
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_CHARACTER_H
#define OPENAO_GAME_MESSAGES_RESPONSES_CHARACTER_H

#include "model/character.h"
#include "serialization/attributes.h"

#include <cstdint>
namespace Game::Messages::Responses {
struct Character {
  static const uint16_t type = 0x02;

  Model::Character c;

  template <typename Archive>
  void serialize(Archive& archive) {
    archive.set(1, 4);
    archive.write(c.position.orientation);
    archive.write(c.position.x);
    archive.write(c.position.y);
    archive.write(c.name);
    archive.write(c.title);
    archive.set(0, 5);
    archive.write(c.shape);
    Serialization::serialize(archive, c.attributes);
    archive.write(c.faction);
    archive.set(0, 4);
    archive.write(c.level);
    archive.write(c.experience);
    archive.set(0, 8);
    archive.set(0, 8);
    archive.write(c.rank);
    archive.write(c.credits);
    archive.set(0, 4);
    archive.write(c.stats.hp_current);
    archive.write(c.stats.hp_total);
    archive.write(c.stats.mp_current);
    archive.write(c.stats.mp_total);
    archive.write(c.stats.sp_current);
    archive.write(c.stats.sp_total);
    archive.write(c.stats.attack_base);
    archive.write(c.stats.attack_right);
    archive.write(c.stats.attack_left);
    archive.write(c.stats.defense_base);
    archive.write(c.stats.defense_total);
    archive.set(0, 8);
    archive.write(c.stats.spell_defense_base);
    archive.write(c.stats.spell_defense_total);
    archive.write(c.stats.rigor_base);
    archive.write(c.stats.rigor_total);
    archive.write(c.stats.agility_base);
    archive.write(c.stats.agility_total);
    archive.write(c.stats.critical_base);
    archive.write(c.stats.critical_total);
    archive.write(c.stats.stamina_base);
    archive.write(c.stats.stamina_total);
    archive.write(c.stats.soul_defense_base);
    archive.write(c.stats.soul_defense_total);
    archive.set(0, 4);
    archive.write(c.stats.thunder_defense_total);
    archive.write(c.stats.thunder_attack_total);
    archive.write(c.stats.fire_defense_total);
    archive.write(c.stats.fire_attack_total);
    archive.write(c.stats.ice_defense_total);
    archive.write(c.stats.ice_attack_total);
    archive.write(c.stats.rotten_defense_total);
    archive.write(c.stats.rotten_attack_total);
    archive.set(0, 4);
    archive.write(c.stats.weight);
    archive.write(c.skills);
  }
};
}

#endif// OPENAO_GAME_MESSAGES_RESPONSES_CHARACTER_H
