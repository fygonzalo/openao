#ifndef OPENAO_GAME_ENTITY_REPOSITORY_H
#define OPENAO_GAME_ENTITY_REPOSITORY_H

#include "schema.h"
#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>

#include "entity/irepository.h"

namespace openao::game::entity {

class Repository : public IRepository {
public:
  Repository(sqlpp::postgresql::connection &db) : db(db) {}

  std::list<NPC> get_npcs_by_stage(int stage) override {
    PUBLICNpc table;
    auto results = db(select(sqlpp::all_of(table))
                              .from(table)
                              .where(table.stage == stage));

    std::list<NPC> npcs;
    for (auto &row: results) {
      auto &npc = npcs.emplace_back();
      npc.id = row.id;
      npc.name = row.name;
      npc.position.x = row.positionX;
      npc.position.y = row.positionY;
      npc.orientation = row.orientation;
      npc.model = row.model;
      npc.level = row.level;
      npc.faction = row.faction;
      npc.type = row.type;
    }
    return npcs;
  }

private:
  sqlpp::postgresql::connection &db;
};

}// namespace openao::game::entity

#endif// OPENAO_GAME_ENTITY_REPOSITORY_H
