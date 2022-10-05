
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_CHARACTER_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_CHARACTER_H

#include "model/character.h"
#include "datasources/impl/pqxx/common/attributes.h"
#include "datasources/impl/pqxx/common/misc.h"
#include "datasources/impl/pqxx/common/position.h"
#include "datasources/impl/pqxx/common/stats.h"
#include "datasources/impl/pqxx/common/equipment.h"

#include "pqxx/row"


namespace Datasources::PQXX {
void deserialize(pqxx::row &r, Model::Character &c) {
  c.id = r["id"].as<int>();
  c.account_id = r["account_id"].as<int>();
  c.index = r["index"].as<int>();
  c.name = r["name"].as<std::string>();
  c.title = r["title"].as<std::string>();

  deserialize(r, c.attributes);
  deserialize(r, c.misc);

  c.level = r["level"].as<int>();
  c.experience = r["experience"].as<int>();
  c.rank = r["rank"].as<int>();
  c.credits = r["credits"].as<int>();
  c.faction = r["faction"].as<int>();
  c.stage = r["stage"].as<int>();

  deserialize(r, c.position);
  deserialize(r, c.equipment);
  c.shape = r["shape"].as<int>();

  deserialize(r, c.stats);
}
}

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_CHARACTER_H
