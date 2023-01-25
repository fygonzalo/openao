#ifndef OPENAO_GAME_INVENTORY_MANAGER_H
#define OPENAO_GAME_INVENTORY_MANAGER_H

#include <list>
#include <unordered_map>

#include "di/injectable.h"

#include "inventory/model/inventory.h"

namespace openao::game::inventory {

struct InventoryKey {
  uint8_t type;
  uint32_t entity;
};

struct InventoryKeyComparer {

  bool operator()(const InventoryKey &k1, const InventoryKey &k2) const {
    bool status = (k1.entity == k2.entity) && (k1.type == k2.type);
    return status;
  }
};


struct InventoryKeyHasher {
  std::size_t operator()(const InventoryKey &k) const {
    using std::hash;
    using std::size_t;

    return ((hash<int>()(k.type) ^ (hash<int>()(k.entity) << 1)) >> 1);
  }
};

class Manager : public openao::framework::di::Injectable {
public:
  model::Inventory &insert(InventoryKey key, model::Inventory &inventory) {
    inventories_[key] = inventory;
    return inventories_.at(key);
  }

  model::Inventory &get(InventoryKey key) { return inventories_[key]; }

  void remove(InventoryKey key) { inventories_.erase(key); }


private:
  std::unordered_map<InventoryKey, model::Inventory, InventoryKeyHasher,
                     InventoryKeyComparer>
          inventories_;
};

}// namespace openao::game::inventory

#endif// OPENAO_GAME_INVENTORY_MANAGER_H
