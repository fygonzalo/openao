#ifndef OPENAO_GAME_CHRACTER_MODEL_CHARACTER_H
#define OPENAO_GAME_CHRACTER_MODEL_CHARACTER_H

#include <cstdint>
#include <string>

namespace openao::game::character::model {

struct Attributes {
  uint8_t gender;
  uint8_t hair_style;
  uint8_t height;
  uint8_t hair_color;
  uint8_t skin_color;
};

struct Misc {

  struct Birthday {
    uint8_t day;
    uint8_t month;
  };

  Birthday birthday;
  uint8_t blood;
  uint8_t place;
  uint8_t job;
  uint8_t face;
  uint8_t personality;
};

struct Stats {

  struct Basic {
    uint32_t current;
    uint32_t total;
  };

  struct Elemental {
    uint16_t defense;
    uint16_t attack;
  };

  struct Some {
    uint16_t base;
    uint16_t total;
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
};

struct Position {
  uint32_t x;
  uint32_t y;
  uint8_t orientation;
};

struct Equipment {
  uint32_t head{0};
  uint32_t body{0};
  uint32_t right_hand{0};
  uint32_t left_hand{0};
  uint32_t hand{0};
  uint32_t feet{0};
  uint32_t back{0};
  uint32_t ride{0};

  void serialize(BinaryBuffer &buffer) {
    buffer.write(head);
    buffer.write(body);
    buffer.write(right_hand);
    buffer.write(left_hand);
    buffer.write(hand);
    buffer.write(feet);
    buffer.write(back);
    buffer.write(ride);
  }
};

struct Character {

  uint32_t id;
  std::string name;
  std::string title;
  Attributes attributes;
  Position position;
  uint32_t shape;
  uint8_t faction;
  Equipment equipment;
  uint32_t level;
  uint64_t experience;
  uint8_t rank;
  uint32_t credits;
  Stats stats;
};

}// namespace openao::game::character::model

#endif// OPENAO_GAME_CHRACTER_MODEL_CHARACTER_H
