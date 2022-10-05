
#ifndef OPENAO_DATASOURCES_IINVENTORY_H
#define OPENAO_DATASOURCES_IINVENTORY_H

#include <vector>

#include "model/inventoryitem.h"

namespace Datasources {

class IInventory {
public:
  virtual Model::Inventory get_bag_items(uint32_t character_id) = 0;
};

}

#endif// OPENAO_DATASOURCES_IINVENTORY_H
