
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_BAGITEMS_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_BAGITEMS_H

#include "repositories/iinventory.h"
#include <pqxx/pqxx>

namespace Repositories::PQXX {

class Inventory : public Repositories::IInventory {
public:
  Inventory(pqxx::connection &connection) : connection_(connection) {}

  std::vector<Model::InventoryItem> get_bag_items(uint32_t character_id) override {
    pqxx::work w{connection_};

    auto result = w.exec("SELECT * FROM bagitem WHERE character_id = " +
                         w.quote(character_id));
    w.commit();

    std::vector<Model::InventoryItem> bag_items;

    for (const auto &r: result) {
      auto &bi = bag_items.emplace_back();
      bi.id = r["id"].as<int>();
      bi.character_id = r["character_id"].as<int>();
      bi.slot = r["slot"].as<int>();
      bi.item_id = r["item_id"].as<int>();
      bi.quantity = r["quantity"].as<int>();
    }

    return bag_items;
  }

private:
  pqxx::connection &connection_;
};

}// namespace Repositories::PQXX

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_BAGITEMS_H
