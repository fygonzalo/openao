#ifndef OPENAO_GAME_INVENTORY_CONTROLLER_H
#define OPENAO_GAME_INVENTORY_CONTROLLER_H

#include "transport/iclient.h"

#include "inventory/commands/loadinventory.h"
#include "inventory/commands/moveitem.h"
#include "inventory/events/loadinventory.h"
#include "inventory/events/updateinventory.h"

#include "inventory/irepository.h"
#include "inventory/manager.h"

#include "character/manager.h"


using namespace openao::game::inventory;

using namespace openao::game;

namespace openao::game::inventory {

class Controller {
public:
  static void load(IClient &client, const commands::LoadInventory &command,
                   IRepository &inventory_repository,
                   inventory::Manager &inventory_manager,
                   character::Manager &character_manager) {

    uint32_t character_id = character_manager.get(&client);
    auto inventory = inventory_repository.get(1, character_id);

    InventoryKey key{1, character_id};
    inventory_manager.insert(key, inventory);

    events::LoadInventory load{};
    load.inventory_type = 1;
    load.owner = character_id;
    load.slots = inventory.all();
    client.send(load);
  }


  static void move_item(IClient &client, const commands::MoveItem &command,
                        character::Manager &character_manager,
                        inventory::Manager &inventory_manager) {
    auto character_id = character_manager.get(&client);
    auto &inventory = inventory_manager.get({1, character_id});

    inventory.move(command.source, command.destination);
    events::UpdateInventory update{};
    update.inventory_type = 1;
    update.owner = character_id;
    update.slots.insert(inventory[command.source]);
    update.slots.insert(inventory[command.destination]);
    client.send(update);
  }
};

}// namespace openao::game::inventory


#endif// OPENAO_GAME_INVENTORY_CONTROLLER_H