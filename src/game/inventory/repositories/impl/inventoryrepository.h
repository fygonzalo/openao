#ifndef OPENAO_GAME_INVENTORY_REPOSITORIES_IMPL_INVENTORYREPOSITORY_H
#define OPENAO_GAME_INVENTORY_REPOSITORIES_IMPL_INVENTORYREPOSITORY_H

#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>

#include "schema.h"

#include "inventory/repositories/iinventoryrepository.h"


using namespace openao::game::inventory::repositories;

namespace openao::game::inventory::repositories::impl {

class InventoryRepository : public IInventoryRepository {
public:
  InventoryRepository(sqlpp::postgresql::connection &conn) : conn_(conn){};

  std::list<Item> get(uint32_t type, uint32_t entity) override {

    PUBLICInventoryitem table;
    auto results = conn_(select(sqlpp::all_of(table))
                                 .from(table)
                                 .where(table.inventoryType == type and
                                        table.entity == entity));

    std::list<Item> inventory{};
    for (const auto &row: results) {
      auto &item = inventory.emplace_back();
      item.id = row.id;
      item.timestamp = row.timestamp;
      item.item = row.item;
      item.type = row.inventoryType;
      item.entity = row.entity;
      item.slot = row.slot;
      item.quantity = row.quantity;
      item.bind = row.bind;
      item.rests = row.restCount;
      item.flags = row.restEnabled;
      item.hardiness = row.hardiness;
      item.timer = row.expiresAt;
      item.piercings = row.piercings;
      item.intensifications = row.intensifications;
    }

    return inventory;
  }

private:
  sqlpp::postgresql::connection &conn_;
};

}// namespace openao::game::inventory::repositories::impl

#endif// OPENAO_GAME_INVENTORY_REPOSITORIES_IMPL_INVENTORYREPOSITORY_H