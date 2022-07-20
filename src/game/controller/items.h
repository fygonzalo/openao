
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
    auto status = inventory_.move_item(1, request.slot_source,
                                       request.slot_destination);


    if (status) {
      auto bag_items = inventory_.get_bag_items(1);
      Model::InventoryItem *bi;
      for (Model::InventoryItem &i: bag_items) {
        if (i.slot == request.slot_destination) bi = &i;
      }

      auto ui = Messages::Responses::UpdateInventory();
      ui.add(std::make_shared<Messages::Responses::AddItem>(*bi));
      ui.add(std::make_shared<Messages::Responses::RemoveItem>(
              1, request.slot_source));

      co_await stream.write(ui);
    }
  }


private:
  Subsystems::Inventory &inventory_;
};// namespace Game::Controller

}// namespace Game::Controller

#endif// OPENAO_GAME_CONTROLLER_ITEMS_H
