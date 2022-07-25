
#ifndef OPENAO_SUBSYSTEMS_INVENTORY_H
#define OPENAO_SUBSYSTEMS_INVENTORY_H

#include <map>
#include <memory>

#include "repositories/iinventory.h"

namespace Game::Subsystems {

class Inventory {

public:
  Inventory(Repositories::IInventory &iinventory) : iinventory_(iinventory) {}

  Model::Inventory& get_inventory(uint32_t character_id) {
    if (!inventory.contains(character_id)) {
      inventory[character_id] = iinventory_.get_bag_items(character_id);
    }
    return inventory[character_id];
  };



private:
  Repositories::IInventory &iinventory_;

  std::map<uint32_t, Model::Inventory> inventory;
};

}// namespace Game::Subsystems

#endif// OPENAO_SUBSYSTEMS_INVENTORY_H
