
#ifndef OPENAO_MODEL_STATS_H
#define OPENAO_MODEL_STATS_H

#include <cstdint>
namespace Model {
struct Stats {
  uint32_t hp_current;
  uint32_t hp_total;

  uint32_t mp_current;
  uint32_t mp_total;

  uint16_t sp_current;
  uint16_t sp_total;

  uint32_t weight;
  uint32_t move_speed;
  uint32_t attack_speed;

  uint32_t attack_base;
  uint32_t attack_right;
  uint32_t attack_left;

  uint32_t defense_base;
  uint32_t defense_total;
  uint32_t spell_defense_base;
  uint32_t spell_defense_total;

  uint16_t rigor_base;
  uint16_t rigor_total;

  uint16_t agility_base;
  uint16_t agility_total;

  uint16_t critical_base;
  uint16_t critical_total;

  uint16_t stamina_base;
  uint16_t stamina_total;

  uint16_t soul_defense_base;
  uint16_t soul_defense_total;

  uint16_t thunder_attack;
  uint16_t thunder_defense;

  uint16_t fire_attack;
  uint16_t fire_defense;

  uint16_t ice_attack;
  uint16_t ice_defense;

  uint16_t rotten_attack;
  uint16_t rotten_defense;
};
}// namespace Model

#endif// OPENAO_MODEL_STATS_H
