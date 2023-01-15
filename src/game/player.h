
#ifndef OPENAO_GAME_PLAYER_H
#define OPENAO_GAME_PLAYER_H

#include <asio.hpp>
#include <chrono>
#include <deque>
#include <optional>

#include "datasources/impl/pqxx/common/character.h"
#include "entitymanager.h"
#include "game/messages/requests/auth.h"
#include "game/messages/requests/loadinventory.h"
#include "game/messages/requests/logout_1.h"
#include "game/messages/requests/move.h"
#include "game/messages/responses/character.h"
#include "game/messages/responses/loadinventory.h"
#include "game/messages/responses/move.h"
#include "game/messages/responses/removeentity.h"
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
  Player(MessageStream stream, pqxx::connection &conn, EntityManager &em, PlayerManager & pm)
      : stream_(std::move(stream)), send_timer_(stream.get_executor()),
        recv_timer_(stream.get_executor()), conn_(conn), em_(em), pm_(pm) {
    send_timer_.expires_at(std::chrono::steady_clock::time_point::max());
  };

  void start() {
    std::cout << "Starting client" << std::endl;
    co_spawn(stream_.get_executor(), writer(), asio::detached);
    co_spawn(stream_.get_executor(), reader(), asio::detached);
    std::cout << "Client started" << std::endl;
  }

  void write(const Message &message) {
    send_queue_.push_back(message);
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
    pm_.create(eid, c, this);
    Messages::Responses::Character charinfo{.entityid = eid, .c = c};
    write(charinfo);
  }

  void load_inventory(const Messages::Requests::LoadInventory &request) {
    auto d = pm_.get(eid);

    pqxx::work w{conn_};
    auto r = w.exec("SELECT * FROM inventoryitem WHERE character_id = " +
                    w.quote(d.first.id));
    w.commit();
    Model::Inventory iv{};

    for (const auto &r_: r) {
      auto ii = Model::InventoryItem();
      ii.id = r_["id"].as<int>();
      ii.character_id = r_["character_id"].as<int>();
      ii.slot = r_["slot"].as<int>();
      ii.code = r_["code"].as<int>();
      ii.quantity = r_["quantity"].as<int>();

      iv.add(ii);
    }

    write(Messages::Responses::LoadInventory{iv});
  }

  void move(const Messages::Requests::Move &request) {
    auto& p = pm_.get(eid);
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

  void logout(const Messages::Requests::Logout1& request) {
    Messages::Responses::RemoveEntity re{.entityid = eid, .code = 0};
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
};
}// namespace Game
#endif// OPENAO_GAME_PLAYER_H
