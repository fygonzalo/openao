#ifndef OPENAO_GAME_INVENTORY_CONTROLLER_H
#define OPENAO_GAME_INVENTORY_CONTROLLER_H

#include "transport/iclient.h"

#include "inventory/commands/loadinventory.h"
#include "inventory/events/loadinventory.h"

#include "inventory/irepository.h"

#include "character/manager.h"


using namespace openao::game::inventory;

using namespace openao::game;

namespace openao::game::inventory {

class Controller {
public:
  static void load(IClient &client, const commands::LoadInventory &command,
                   IRepository &inventory_repository,
                   character::Manager &character_manager) {

    uint32_t &character_id = character_manager[&client];
    auto inventory = inventory_repository.get(1, character_id);

    events::LoadInventory event;
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


#endif// OPENAO_GAME_INVENTORY_CONTROLLER_H