
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
  Items(Subsystems::EntityManager &entity_manager) : entity_manager_(entity_manager) {}

  awaitable<void> move_item(MessageStream &stream,
                            Messages::Requests::MoveItem &request) {

    auto& inventory = entity_manager_.find_by_character_id(1).items;
    auto& item = inventory.move(request.slot_source, request.slot_destination);

    auto ui = Messages::Responses::UpdateInventory();
    ui.add(std::make_shared<Messages::Responses::AddItem>(item));
    ui.add(std::make_shared<Messages::Responses::RemoveItem>(
            1, request.slot_source));

    co_await stream.write(ui);

    Messages::Responses::EntityAction ea{};
    ea.entity = 1;
    ea.item = item.item_id;
    ea.slot = item.slot;

    for (Subsystems::Entity& e : entity_manager_.get_all()) {
      if (e.id != 1) {
        co_await e.stream->write(ea);
      }
    }
  }


private:
  Subsystems::EntityManager &entity_manager_;
};// namespace Game::Controller

}// namespace Game::Controller

#endif// OPENAO_GAME_CONTROLLER_ITEMS_H
