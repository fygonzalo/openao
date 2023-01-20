#ifndef OPENAO_GAME_INVENTORY_INVENTORYCONTROLLER_H
#define OPENAO_GAME_INVENTORY_INVENTORYCONTROLLER_H

#include "inventory/commands/loadinventorycommand.h"
#include "inventory/events/loadinventoryevent.h"
#include "transport/iclient.h"


using namespace openao::game::inventory::commands;
using namespace openao::game::inventory::events;

namespace openao::game::inventory {

class InventoryController {
public:
  static void load_inventory(IClient &client,
                             const LoadInventoryCommand &command) {
    LoadInventoryEvent event;
    client.send(event);
  }
};

}// namespace openao::game::inventory


#endif// OPENAO_GAME_INVENTORY_INVENTORYCONTROLLER_H