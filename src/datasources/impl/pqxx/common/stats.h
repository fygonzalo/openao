
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_STATS_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_STATS_H

#include "model/character.h"
#include <pqxx/pqxx>

namespace Datasources::PQXX {
void deserialize(pqxx::row &r, Model::Stats &s) {

  s.hp_current = r["hp_current"].as<int>();
  s.hp_total = r["hp_total"].as<int>();

  s.mp_current = r["mp_current"].as<int>();
  s.mp_total = r["mp_total"].as<int>();

  s.sp_current = r["sp_current"].as<int>();
  s.sp_total = r["sp_total"].as<int>();

  s.weight = r["weight"].as<int>();
  s.attack_base = r["attack_base"].as<int>();
  s.attack_right = r["attack_right"].as<int>();
  s.attack_left = r["attack_left"].as<int>();

  s.defense_base = r["defense_base"].as<int>();
  s.defense_total = r["defense_total"].as<int>();

  s.spell_defense_base = r["spell_defense_base"].as<int>();
  s.spell_defense_total = r["spell_defense_total"].as<int>();

  s.rigor_base = r["rigor_base"].as<int>();
  s.rigor_total = r["rigor_total"].as<int>();

  s.agility_base = r["agility_base"].as<int>();
  s.agility_total = r["agility_total"].as<int>();

  s.critical_base = r["critical_base"].as<int>();
  s.critical_total = r["critical_total"].as<int>();

  s.stamina_base = r["stamina_base"].as<int>();
  s.stamina_total = r["stamina_total"].as<int>();

  s.soul_defense_base = r["soul_defense_base"].as<int>();
  s.soul_defense_total = r["soul_defense_total"].as<int>();

  s.thunder_attack_total = r["thunder_attack_total"].as<int>();
  s.thunder_defense_total = r["thunder_defense_total"].as<int>();

  s.fire_attack_total = r["fire_attack_total"].as<int>();
  s.fire_defense_total = r["fire_defense_total"].as<int>();

  s.fire_attack_total = r["ice_attack_total"].as<int>();
  s.fire_defense_total = r["ice_defense_total"].as<int>();

  s.rotten_attack_total = r["rotten_attack_total"].as<int>();
  s.rotten_defense_total = r["rotten_defense_total"].as<int>();
}
}// namespace Repositories::PQXX

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_STATS_H
