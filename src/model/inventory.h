
#ifndef OPENAO_MODEL_INVENTORY_H
#define OPENAO_MODEL_INVENTORY_H

#include <map>

namespace Model {

class Inventory {
public:
  class InventoryItem {
  public:
  private:
  };


  InventoryItem &operator[](int index) { return inventory_.at(index); }

private:
  std::map<int, InventoryItem> inventory_;
};

}// namespace Model

#endif// OPENAO_MODEL_INVENTORY_H
