
#ifndef OPENAO_SUBSYSTEMS_INVENTORY_H
#define OPENAO_SUBSYSTEMS_INVENTORY_H

#include <map>
#include <memory>

#include "repositories/iinventory.h"

namespace Game::Subsystems {

class Inventory {

public:
  Inventory(Repositories::IInventory &iinventory) : iinventory_(iinventory) {}

  std::vector<Model::BagItem> get_bag_items(uint32_t character_id) {
    if (!bagitems.contains(character_id)) {
      bagitems[character_id] = iinventory_.get_bag_items(character_id);
    }
    return bagitems[character_id];
  };

  bool move_item(uint32_t character_id, uint16_t source, uint16_t destination) {
    auto &bi = bagitems.at(character_id);
    for (auto &i: bi) {
      if (i.slot == source) {
        i.slot = destination;
        return true;
      }
    }

    return false;
  }



private:
  Repositories::IInventory &iinventory_;

  std::map<uint32_t, std::vector<Model::BagItem>> bagitems;
};

}// namespace Game::Subsystems

#endif// OPENAO_SUBSYSTEMS_INVENTORY_H
