
#ifndef OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_CHARACTERLISTEVENT_H
#define OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_CHARACTERLISTEVENT_H

#include "experimental/reactor/event.h"
#include "utils/binarybuffer.h"
#include "utils/string.h"

using namespace openao::experimental::reactor;

namespace openao::experimental::login::account {

struct CharacterListEvent : Event<CharacterListEvent> {

  struct Character {

    struct Attributes {
      uint8_t gender;
      uint8_t hair_style;
      uint8_t height;
      uint8_t hair_color;
      uint8_t skin_color;

      void serialize(BinaryBuffer &buffer) {
        buffer.write(gender);
        buffer.write(hair_style);
        buffer.write(height);
        buffer.write(hair_color);
        buffer.write(skin_color);
      }
    };

    struct Equipment {
      uint32_t head;
      uint32_t body;
      uint32_t right_hand;
      uint32_t left_hand;
      uint32_t hand;
      uint32_t feet;
      uint32_t back;
      uint32_t ride;

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

    struct Stats {
      uint32_t current_hp;
      uint32_t current_mp;

      void serialize(BinaryBuffer &buffer) {
        buffer.write(current_hp);
        buffer.write((uint32_t) 0);
        buffer.write(current_mp);
        buffer.write((uint32_t) 0);
      }
    };

    uint32_t level;
    uint8_t faction;
    Attributes attributes;
    uint32_t stage;
    uint8_t status_flags;
    uint32_t shape;
    uint32_t deletion_timer;
    uint32_t character_id;
    String character_name{16};
    uint32_t account_id;
    String account_name{20};
    Equipment equipment;
    Stats stats;
    String title{12};

    void serialize(BinaryBuffer &buffer) {
      buffer.write(level);
      buffer.write(faction);
      buffer.write(attributes);
      buffer.write(stage);
      buffer.set(0, 3);
      buffer.write(status_flags);
      buffer.write(shape);
      buffer.write(deletion_timer);
      buffer.write((uint32_t) 0);
      buffer.write(character_id);
      buffer.write(character_name);
      buffer.write(account_id);
      buffer.write(account_name);
      buffer.write(equipment);
      buffer.write(stats);
      buffer.write(title);
      buffer.write((uint32_t) 0);
    }
  };

  struct Branches {
    std::vector<uint32_t> statuses;

    void serialize(BinaryBuffer & buffer) {
      buffer.write((uint32_t)statuses.size());
      buffer.set(0, 51);
      buffer.write(statuses);
    }
  };

  static const uint16_t error_code = 0;
  bool requires_pin;
  std::array<Character, 3> characters;
  std::array<uint8_t, 3> birthday_months;
  std::array<uint8_t, 3> birthday_days;
  std::array<uint8_t, 3> blood_types;
  std::array<uint32_t, 3> total_hps;
  std::array<uint32_t, 3> total_mps;
  std::array<std::array<uint32_t, 9>, 3> active_skills;
  uint32_t active_character_slots;
  Branches branches;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(error_code);
    buffer.write(requires_pin);
    for (int i = 0; i < characters.size(); i++) {
      buffer.write((uint8_t) i);
      buffer.write(characters[i]);
    }
    buffer.write(birthday_months);
    buffer.write(birthday_days);
    buffer.write(blood_types);
    buffer.write(total_hps);
    buffer.write(total_mps);
    buffer.write(active_skills);
    buffer.write(active_character_slots);
    buffer.write(branches);
  }
};

}// namespace openao::experimental::login::account

#endif// OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_CHARACTERLISTEVENT_H
