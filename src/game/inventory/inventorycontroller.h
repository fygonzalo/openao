#ifndef OPENAO_GAME_INVENTORY_INVENTORYCONTROLLER_H
#define OPENAO_GAME_INVENTORY_INVENTORYCONTROLLER_H

#include "transport/iclient.h"

#include "inventory/commands/loadinventorycommand.h"
#include "inventory/events/loadinventoryevent.h"
#include "inventory/repositories/iinventoryrepository.h"

#include "character/charactermanager.h"


using namespace openao::game::inventory::commands;
using namespace openao::game::inventory::events;
using namespace openao::game::inventory::repositories;

using namespace openao::game::character;

namespace openao::game::inventory {

class InventoryController {
public:
  static void load_inventory(IClient &client,
                             const LoadInventoryCommand &command,
                             IInventoryRepository &inventory_repository,
                             CharacterManager &character_manager) {

    uint32_t &character_id = character_manager[&client];
    auto inventory = inventory_repository.get(1, character_id);

    LoadInventoryEvent event;
    for (auto &i: inventory) {
      auto &item = event.items.emplace_back();
      item.id = i.id;
      item.timestamp = i.timestamp;
      item.code = i.item;
      item.type = i.type;
      item.entity = i.entity;
      item.slot = i.slot;
      item.quantity = i.quantity;
      item.bind = i.bind;
      item.rests = i.rests;
      item.flags = i.flags;
      item.hardiness = i.hardiness;
      item.timer = i.timer;
      item.piercings = i.piercings;
      item.intensifications = i.intensifications;
    }


    client.send(event);
  }
};

}// namespace openao::game::inventory


#endif// OPENAO_GAME_INVENTORY_INVENTORYCONTROLLER_H