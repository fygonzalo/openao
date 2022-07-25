
#ifndef OPENAO_REPOSITORIES_IINVENTORY_H
#define OPENAO_REPOSITORIES_IINVENTORY_H

#include <vector>

#include "model/inventoryitem.h"

namespace Repositories {

class IInventory {
public:
  virtual Model::Inventory get_bag_items(uint32_t character_id) = 0;
};

}

#endif// OPENAO_REPOSITORIES_IINVENTORY_H
