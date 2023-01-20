#ifndef OPENAO_GAME_CHARACTER_EVENTS_CHARACTERDETAILEVENT_H
#define OPENAO_GAME_CHARACTER_EVENTS_CHARACTERDETAILEVENT_H

#include "event.h"
#include "utils/binarybuffer.h"
#include "utils/bitset.h"
#include "utils/string.h"

using namespace openao::framework::utils;

namespace openao::game::character::events {

struct CharacterDetailEvent : framework::IEvent {
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

  struct Position {
    uint32_t x;
    uint32_t y;

    void serialize(BinaryBuffer &buffer) {
      buffer.write(x);
      buffer.write(y);
    }
  };

  struct Attributes {
    uint8_t gender{0};
    uint8_t hair_style{0};
    uint8_t height{0};
    uint8_t hair_color{0};
    uint8_t skin_color{0};

    void serialize(BinaryBuffer &buffer) {
      buffer.write(gender);
      buffer.write(hair_style);
      buffer.write(height);
      buffer.write(hair_color);
      buffer.write(skin_color);
    }
  };

  struct Stats {

    struct Basic {
      uint32_t current;
      uint32_t total;

      void serialize(BinaryBuffer &buffer) {
        buffer.write(current);
        buffer.write(total);
      }
    };

    struct Elemental {
      uint16_t defense;
      uint16_t attack;

      void serialize(BinaryBuffer &buffer) {
        buffer.write(defense);
        buffer.write(attack);
      }
    };

    struct Some {
      uint16_t base;
      uint16_t total;

      void serialize(BinaryBuffer &buffer) {
        buffer.write(base);
        buffer.write(total);
      }
    };

    Basic hp;
    Basic mp;
    Some sp;
    uint32_t attack_base;
    uint32_t attack_right;
    uint32_t attack_left;
    Basic defense;
    Basic spell_attack;
    Basic spell_defense;
    Some rigor;
    Some agility;
    Some critical;
    Some stamina;
    Some soul_defense;
    Elemental thunder;
    Elemental fire;
    Elemental ice;
    Elemental rotten;
    Basic weight;


    void serialize(BinaryBuffer &buffer) {
      buffer.write(hp);
      buffer.write(mp);
      buffer.write(sp);
      buffer.write(attack_base);
      buffer.write(attack_right);
      buffer.write(attack_left);
      buffer.write(defense);
      buffer.write(spell_attack);
      buffer.write(spell_defense);
      buffer.write(rigor);
      buffer.write(agility);
      buffer.write(critical);
      buffer.write(stamina);
      buffer.write(soul_defense);
      buffer.set(0, 4);
      buffer.write(thunder);
      buffer.write(fire);
      buffer.write(ice);
      buffer.write(rotten);
      buffer.write(weight);
    }
  };

  uint32_t entityid;
  Position position;
  String name{16};
  String title{12};
  uint8_t orientation;
  uint32_t shape;
  Attributes attributes;
  uint8_t faction;
  uint32_t level;
  uint64_t experience;
  uint8_t rank;
  uint32_t credits;
  Stats stats;
  uint32_t character_id;

  Skill skills[36];
  Bitset<8192> spells;
  Bitset<1032> crowns;
  Bitset<3752> recipes;
  Bitset<360> cards;
  Bitset<88> cardsets;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(entityid);
    buffer.set(0, 4);
    buffer.write(position);
    buffer.write(name);
    buffer.write(title);
    buffer.set(0, 4);
    buffer.write(orientation);
    buffer.write(shape);
    buffer.write(attributes);
    buffer.write(faction);
    buffer.set(0, 4);
    buffer.write(level);
    buffer.write(experience);
    buffer.set(0, 8);
    buffer.set(0, 8);
    buffer.write(rank);
    buffer.write(credits);
    buffer.set(0, 4);
    buffer.write(stats);
    buffer.write((uint32_t) 0);
    buffer.write(character_id);// Not sure


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
    for (int i = 0; i < 36; i++) { buffer.write(sk[i]); }

    buffer.write(spells);

    buffer.write(crowns);

    // Unknown
    buffer.write((uint32_t) 0);

    buffer.write(recipes);

    // Unknown
    buffer.set(0x00, 1579);

    // Unknown
    buffer.set(0x00, 12);

    // Trade Password
    buffer.set(0x00, 1);

    // Unknown
    buffer.set(0x00, 21);

    buffer.write(cards);

    // Unknown
    buffer.set(0x00, 83);

    cardsets[2].flip();
    buffer.write(cardsets);

    // Unknown
    buffer.set(0x00, 22);
  }
};


}// namespace openao::game::character::events


#endif// OPENAO_GAME_CHARACTER_EVENTS_CHARACTERDETAILEVENT_H