
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_CHARACTER_H
#define OPENAO_GAME_MESSAGES_RESPONSES_CHARACTER_H

#include "model/character.h"
#include "serialization/attributes.h"
#include "utils/bitset.h"

#include <cstdint>

namespace Game::Messages::Responses {
struct Character {
  struct Skill {
    uint8_t id;
    uint16_t current;
    uint16_t next;
    uint32_t experience;
    uint32_t required;
    uint8_t order;

    void serialize(BinaryBuffer &buffer) {
      buffer.write(id);
      buffer.write(current);
      buffer.write(next);
      buffer.write(experience);
      buffer.write(required);
      buffer.write(order);
    }
  };

  static const uint16_t type = 0x02;

  uint32_t entityid;
  Model::Character c;

  template<typename Archive>
  void serialize(Archive &archive) {
    archive.write(entityid);
    archive.set(0, 4);
    archive.write(c.position.x);
    archive.write(c.position.y);
    archive.write(c.name);
    archive.write(c.title);
    archive.set(0, 4);
    archive.write(c.position.orientation);
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
    archive.write((uint32_t) 0);
    archive.write(c.id);// Not sure

    Skill sk[]{
            {2, 199, 199, 178874, 264070, 1},
            {3, 215, 215, 18687, 221029, 2},
            {4, 158, 158, 74171, 149056, 3},
            {34, 143, 143, 114059, 235270, 4},
            {35, 143, 143, 8582, 235270, 5},
            {36, 218, 218, 1177, 117975, 6},
            {1, 143, 143, 114059, 235270, 0},
            {5, 143, 143, 114059, 235270, 0},
            {6, 143, 143, 114059, 235270, 0},
            {7, 143, 143, 114059, 235270, 0},
            {8, 143, 143, 114059, 235270, 0},
            {9, 143, 143, 114059, 235270, 0},
            {10, 143, 143, 114059, 235270, 0},
            {11, 143, 143, 114059, 235270, 0},
            {12, 143, 143, 114059, 235270, 0},
            {13, 143, 143, 114059, 235270, 0},
            {14, 143, 143, 114059, 235270, 0},
            {15, 143, 143, 114059, 235270, 0},
            {16, 143, 143, 114059, 235270, 0},
            {17, 143, 143, 114059, 235270, 0},
            {18, 143, 143, 114059, 235270, 0},
            {19, 143, 143, 114059, 235270, 0},
            {20, 143, 143, 114059, 235270, 0},
            {21, 143, 143, 114059, 235270, 0},
            {22, 143, 143, 114059, 235270, 0},
            {23, 143, 143, 114059, 235270, 0},
            {24, 143, 143, 114059, 235270, 0},
            {25, 143, 143, 114059, 235270, 0},
            {26, 143, 143, 114059, 235270, 0},
            {27, 143, 143, 114059, 235270, 0},
            {28, 143, 143, 114059, 235270, 0},
            {29, 143, 143, 114059, 235270, 0},
            {30, 143, 143, 114059, 235270, 0},
            {31, 143, 143, 114059, 235270, 0},
            {32, 143, 143, 114059, 235270, 0},
            {33, 143, 143, 114059, 235270, 0},
    };
    for (int i = 0; i < 36; i++) { archive.write(sk[i]); }

    // Spells
    Bitset<8192> spells;
    archive.write(spells);

    Bitset<1032> crowns;
    archive.write(crowns);

    // Unknown
    archive.write((uint32_t) 0);

    Bitset<3752> recipes;
    archive.write(recipes);

    // Unknown
    archive.set(0x00, 1579);

    // Unknown
    archive.set(0x00, 12);

    // Trade Password
    archive.set(0x00, 1);

    // Unknown
    archive.set(0x00, 21);

    Bitset<360> cards;
    archive.write(cards);

    // Unknown
    archive.set(0x00, 83);

    Bitset<88> cardsets;
    cardsets[1].flip();
    archive.write(cardsets);

    // Unknown
    archive.set(0x00, 51);
  }
};
}// namespace Game::Messages::Responses

#endif// OPENAO_GAME_MESSAGES_RESPONSES_CHARACTER_H
