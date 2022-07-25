
#ifndef OPENAO_GAME_CONTROLLER_ITEMS_H
#define OPENAO_GAME_CONTROLLER_ITEMS_H

#include <asio.hpp>

#include "game/messages/requests/moveitem.h"
#include "game/messages/responses/updateinventory.h"
#include "game/subsystems/inventory.h"
#include "transport/messagestream.h"

namespace Game::Controller {

class Items {
public:
  Items(Subsystems::Inventory &inventory) : inventory_(inventory) {}

  awaitable<void> move_item(MessageStream &stream,
                            Messages::Requests::MoveItem &request) {

    auto& inventory = inventory_.get_inventory(1);
    auto& item = inventory.move(request.slot_source, request.slot_destination);

    auto ui = Messages::Responses::UpdateInventory();
    ui.add(std::make_shared<Messages::Responses::AddItem>(item));
    ui.add(std::make_shared<Messages::Responses::RemoveItem>(
            1, request.slot_source));

    co_await stream.write(ui);
  }


private:
  Subsystems::Inventory &inventory_;
};// namespace Game::Controller

}// namespace Game::Controller

#endif// OPENAO_GAME_CONTROLLER_ITEMS_H
