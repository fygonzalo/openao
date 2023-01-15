
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_BAGITEMS_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_BAGITEMS_H

#include "datasources/iinventory.h"
#include <pqxx/pqxx>

namespace Datasources::PQXX {

class Inventory : public Datasources::IInventory {
public:
  Inventory(pqxx::connection &connection) : connection_(connection) {}

  Model::Inventory get_bag_items(uint32_t character_id) override {
    pqxx::work w{connection_};

    auto result = w.exec("SELECT * FROM inventoryitem WHERE character_id = " +
                         w.quote(character_id));
    w.commit();

    Model::Inventory inventory;

    for (const auto &r: result) {
      auto ii = Model::InventoryItem();
      ii.id = r["id"].as<int>();
      ii.inventory_type = r["inventory_type"].as<int>();
      ii.entity = r["character_id"].as<int>();
      ii.slot = r["slot"].as<int>();
      ii.item = r["code"].as<int>();
      ii.quantity = r["quantity"].as<int>();

      inventory.add(ii);
    }

    return inventory;
  }

private:
  pqxx::connection &connection_;
};

}// namespace Datasources::PQXX

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_BAGITEMS_H
