#ifndef OPENAO_GAME_INVENTORY_REPOSITORY_H
#define OPENAO_GAME_INVENTORY_REPOSITORY_H

#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>

#include "inventory/irepository.h"
#include "schema.h"


namespace openao::game::inventory {

class Repository : public IRepository {
public:
  Repository(sqlpp::postgresql::connection &conn) : conn_(conn){};

  model::Inventory get(uint32_t type, uint32_t entity) override {
    PUBLICInventoryitem table;
    auto results = conn_(select(sqlpp::all_of(table))
                                 .from(table)
                                 .where(table.inventoryType == type and
                                        table.entity == entity));

    model::Inventory inventory;
    for (const auto &row: results) {
      auto [pos, item] = inventory[row.slot];
      item.id = row.id;
      item.timestamp = row.timestamp;
      item.code = row.item;
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
  };

private:
  sqlpp::postgresql::connection &conn_;
};

}// namespace openao::game::inventory

#endif// OPENAO_GAME_INVENTORY_REPOSITORY_H