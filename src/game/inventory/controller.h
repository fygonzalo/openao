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
#include "entity/events/update.h"


using namespace openao::game::inventory;

using namespace openao::game;

namespace openao::game::inventory {

class Controller {
public:
  static void load(IClient &client, const commands::LoadInventory &command,
                   IRepository &inventory_repository,
                   inventory::Manager &inventory_manager,
                   character::Manager &character_manager,
                   entity::Manager &entity_manager,
                   stage::Manager &stage_manager) {

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


  static uint32_t choose(model::Inventory &inventory, uint16_t first,
                         uint16_t second) {
    return inventory[first].second ? inventory[first].second
                                   : inventory[second].second;
  }

  static void move_item(IClient &client, const commands::MoveItem &command,
                        character::Manager &character_manager,
                        inventory::Manager &inventory_manager,
                        entity::Manager& entity_manager,
                        stage::Manager& stage_manager) {
    auto character_id = character_manager.get(&client);
    auto &inventory = inventory_manager.get({1, character_id});

    inventory.move(command.source, command.destination);
    events::UpdateInventory update{};
    update.inventory_type = 1;
    update.owner = character_id;
    update.slots.insert(inventory[command.source]);
    update.slots.insert(inventory[command.destination]);
    client.send(update);



    if (command.source >= 1 and command.source <= 10 or
        command.source >= 167 and command.source <= 175 or
        command.destination >= 1 and command.destination <= 10 or
        command.destination >= 167 and command.destination <= 175) {

      auto *entity = entity_manager.get(character_id);
      entity->equipment.head = choose(inventory, 167, 1);
      entity->equipment.body = choose(inventory, 168, 2);
      entity->equipment.right_hand = choose(inventory, 169, 3);
      entity->equipment.left_hand = choose(inventory, 170, 4);
      entity->equipment.hand = choose(inventory, 171, 5);
      entity->equipment.feet = choose(inventory, 172, 6);
      entity->equipment.back = choose(inventory, 173, 7);
      entity->equipment.ride = choose(inventory, 174, 10);

      entity::events::Update update{};
      update.entity = entity->entityid;
      entity::events::Update::Event &event = update.events.emplace_back();
      event.code = 1;
      if (command.destination >= 1 and command.destination <= 10 or
          command.destination >= 167 and command.destination <= 175) {
        event.first = command.destination;
        event.second = inventory[command.destination].second;
      } else {
        event.first = command.source;
        event.second = inventory[command.source].second;
      }
      stage_manager.broadcast(update);
    }
  }
};

}// namespace openao::game::inventory


#endif// OPENAO_GAME_INVENTORY_CONTROLLER_H