
#ifndef OPENAO_GAME_CONTROLLER_ITEMS_H
#define OPENAO_GAME_CONTROLLER_ITEMS_H

#include <asio.hpp>

#include "game/messages/requests/moveitem.h"
#include "game/messages/responses/entityaction.h"
#include "game/messages/responses/updateinventory.h"
#include "game/subsystems/inventory.h"
#include "transport/messagestream.h"

namespace Game::Controller {

class Items {
public:
  Items(Subsystems::EntityManager &entity_manager)
      : entity_manager_(entity_manager) {}

  void move_item(MessageStream &stream, Messages::Requests::MoveItem &request) {

    auto &entity = entity_manager_.find_by_stream(stream);
    auto &inventory = entity.items;
    auto &item = inventory.move(request.slot_source, request.slot_destination);

    auto ui = Messages::Responses::UpdateInventory();
    ui.add(std::make_shared<Messages::Responses::AddItem>(item));
    ui.add(std::make_shared<Messages::Responses::RemoveItem>(
            entity.id, request.slot_source));

    stream.write(ui);

    Messages::Responses::EntityAction ea{};
    ea.entity = entity.id;
    ea.code = item.code;
    ea.slot = item.slot;

    for (Subsystems::Entity &e: entity_manager_.get_all()) {
      if (e.id != entity.id) { e.stream->write(ea); }
    }
  }


private:
  Subsystems::EntityManager &entity_manager_;
};// namespace Game::Controller

}// namespace Game::Controller

#endif// OPENAO_GAME_CONTROLLER_ITEMS_H
