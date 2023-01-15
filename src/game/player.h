
#ifndef OPENAO_GAME_PLAYER_H
#define OPENAO_GAME_PLAYER_H

#include <asio.hpp>
#include <chrono>
#include <deque>
#include <optional>

#include "datasources/impl/pqxx/common/character.h"
#include "entitymanager.h"
#include "game/messages/requests/auth.h"
#include "game/messages/requests/global_message.h"
#include "game/messages/requests/loadinventory.h"
#include "game/messages/requests/logout_1.h"
#include "game/messages/requests/logout_2.h"
#include "game/messages/requests/move.h"
#include "game/messages/requests/moveitem.h"
#include "game/messages/responses/character.h"
#include "game/messages/responses/enable_ui.h"
#include "game/messages/responses/entityaction.h"
#include "game/messages/responses/friendlist.h"
#include "game/messages/responses/global_message.h"
#include "game/messages/responses/inventory_event.h"
#include "game/messages/responses/loadinventory.h"
#include "game/messages/responses/move.h"
#include "game/messages/responses/removeentity.h"
#include "game/messages/responses/set_timestamp.h"
#include "game/messages/responses/test.h"
#include "game/messages/responses/updateinventory.h"
#include "playermanager.h"
#include "transport/messagestream.h"
#include <pqxx/connection>
#include <pqxx/pqxx>


namespace Game {
/**
 * Provides a safe concurrent interface to comunicate with clients.
 */
class Player {

public:
  Player(MessageStream stream, pqxx::connection &conn, EntityManager &em,
         PlayerManager &pm)
      : stream_(std::move(stream)), send_timer_(stream.get_executor()),
        recv_timer_(stream.get_executor()), conn_(conn), em_(em), pm_(pm) {
    send_timer_.expires_at(std::chrono::steady_clock::time_point::max());
  };

  void start() {
    co_spawn(stream_.get_executor(), writer(), asio::detached);
    co_spawn(stream_.get_executor(), reader(), asio::detached);
  }

  void write(Message message) {
    send_queue_.push_back(std::move(message));
    send_timer_.cancel_one();
  }

  void disconnect() {
    close_ = true;
    em_.destroy(eid);
    pm_.destroy(eid);
    send_timer_.cancel_one();
  }

  bool is_open() {
    try {
      return stream_.socket().is_open();
    } catch (std::exception &e) { return false; }
  }

  friend bool operator==(const Player &c1, const Player &c2) {
    return &c1.stream_.socket() == &c2.stream_.socket();
  }

  void authenticate(const Messages::Requests::Auth &request) {
    pqxx::work w{conn_};
    auto r = w.exec("SELECT * FROM character WHERE id =" +
                    w.quote(request.character_id));
    w.commit();

    if (r.size() != 1) disconnect();

    Model::Character c{};
    auto rr = r[0];
    Datasources::PQXX::deserialize(rr, c);

    eid = em_.create();
    Messages::Responses::Character charinfo{.entityid = eid, .c = c};
    write(charinfo);

    pm_.create(eid, c, this);

    Messages::Responses::SpellBar spellbar{};
    write(spellbar);

    Messages::Responses::SetTimestamp ts{1673048443};
    write(ts);

    Messages::Responses::Test test{};
    write(test);
  }

  void load_inventory(const Messages::Requests::LoadInventory &request) {
    // ID | CreationTimestamp | InventoryType | Owner | Slot | Item | Quantity |
    // Flags | Timer | Bind | Rests | Hardiness | Bonus | Intensifications |
    // Piercings | Gems
    auto d = pm_.get(eid);

    pqxx::work w{conn_};
    auto r = w.exec("SELECT * FROM inventoryitem WHERE entity = " +
                    w.quote(d.first.id) + "AND inventory_type = 1");
    w.commit();

    for (const auto &r_: r) {
      auto ii = Model::InventoryItem();
      ii.id = r_["id"].as<int>();
      ii.inventory_type = r_["inventory_type"].as<int>();
      ii.entity = r_["entity"].as<int>();
      ii.slot = r_["slot"].as<int>();
      ii.item = r_["item"].as<int>();
      ii.quantity = r_["quantity"].as<int>();

      inventory_.add(ii);
    }

    write(Messages::Responses::LoadInventory{inventory_});
  }

  void move_item(const Messages::Requests::MoveItem &request) {
    auto& inventory_item = inventory_.get(request.slot_source);

    pqxx::result r;
    try {
      pqxx::work w(conn_);
      r = w.exec("UPDATE inventoryitem SET slot = " +
                            w.quote((int) request.slot_destination) +
                            "WHERE id = " + w.quote((int) inventory_item.id));
      w.commit();
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
      return;
    }

    inventory_item.slot = request.slot_destination;

    Messages::Responses::InventoryEvent ie{};
    ie.events.emplace_back(
            std::make_unique<Messages::Responses::InventoryEvent::Add>(
                    inventory_item));
    ie.events.emplace_back(
            std::make_unique<Messages::Responses::InventoryEvent::Remove>(
                    inventory_item.inventory_type, inventory_item.entity,
                    request.slot_source));

    write(std::move(ie));

    Messages::Responses::EntityAction ea{};
    ea.code = inventory_item.item;
    ea.entity = eid;
    ea.slot = request.slot_destination;

    pm_.broadcast(ea);
  }

  void chat(const Messages::Requests::GlobalMessage &message) {
    auto& p = pm_.get(eid);

    pm_.broadcast(Messages::Responses::GlobalMessage{eid, p.first.name, message.message});
  }

  void move(const Messages::Requests::Move &request) {
    auto &p = pm_.get(eid);
    p.first.position.x = request.destination.x / 32;
    p.first.position.y = request.destination.y / 32;

    Messages::Responses::Move move{
            .entityid = eid,
            .source = {.x = request.source.x, .y = request.source.y},
            .destination =
                    {
                            .x = request.destination.x,
                            .y = request.destination.y,
                    },
            .speed = 150,
    };

    pm_.broadcast(move);
  }

  void logout(const Messages::Requests::Logout1 &request) {
    Messages::Responses::RemoveEntity re{.entityid = eid, .code = 1};
    pm_.destroy(eid);
    pm_.broadcast(re);
    disconnect();
  }

protected:
  virtual awaitable<void> reader() {
    try {
      while (true) {
        std::cout << "Awaiting for message" << std::endl;
        Message message = co_await stream_.read();
        std::cout << "Processing message " << message.header.type << std::endl;
        switch (message.header.type) {
          case Messages::Requests::Auth::type:
            authenticate(message.read<Messages::Requests::Auth>());
            break;
          case Messages::Requests::LoadInventory::type:
            load_inventory(message.read<Messages::Requests::LoadInventory>());
            break;
          case Messages::Requests::Move::type:
            move(message.read<Messages::Requests::Move>());
            break;
          case Messages::Requests::Logout1::type:
            logout(message.read<Messages::Requests::Logout1>());
            break;
          case 14:
            chat(message.read<Messages::Requests::GlobalMessage>());
            break;
          case Messages::Requests::MoveItem::type:
            move_item(message.read<Messages::Requests::MoveItem>());
        }
      }
    } catch (std::exception &e) { disconnect(); }
  }

  awaitable<void> writer() {
    while (true) {

      std::error_code ec;
      co_await send_timer_.async_wait(redirect_error(use_awaitable, ec));

      while (!send_queue_.empty()) {
        co_await stream_.write(send_queue_.front());
        send_queue_.pop_front();
      }

      if (close_) stream_.close();
    }
  }

protected:
  MessageStream stream_;

  asio::steady_timer send_timer_;
  std::deque<Message> send_queue_;

  asio::steady_timer recv_timer_;
  std::chrono::steady_clock::time_point deadline;

  std::deque<Message> recv_queue_;

  bool close_ = false;

  pqxx::connection &conn_;

  Entity eid;

  EntityManager &em_;
  PlayerManager &pm_;

  Model::Inventory inventory_;
};
}// namespace Game
#endif// OPENAO_GAME_PLAYER_H
