#ifndef OPENAO_GAME_ENTITY_MODEL_CHARACTER_H
#define OPENAO_GAME_ENTITY_MODEL_CHARACTER_H

#include "event.h"
#include "utils/binarybuffer.h"
#include "utils/string.h"

using namespace openao::framework::utils;

namespace openao::game::entity {

struct Character : public framework::IEvent {

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

  struct League {
    uint8_t badge;
    String name{12};

    void serialize(BinaryBuffer &buffer) {
      buffer.write(badge);
      buffer.write(name);
    }
  };

  uint32_t entityid;
  uint8_t status;// 8 = DEAD
  Position position;
  String name{16};
  String title{12};
  uint8_t orientation;
  uint32_t shape;
  Attributes attributes;
  uint8_t faction;
  Equipment equipment;
  uint16_t quest_title;
  uint32_t overlay;
  League league;
  uint32_t character_id;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(entityid);
    buffer.set(0, 3);
    buffer.write(status);
    buffer.write(position);
    buffer.write(name);

    buffer.write(title);
    buffer.write((uint32_t) 0x00);

    buffer.write(orientation);
    buffer.write(shape);
    buffer.write(attributes);
    buffer.write(faction);


    buffer.set(0, 1);// ?
    buffer.set(0, 2);// Team ?
    buffer.write(equipment);
    buffer.write((uint32_t) 0);
    buffer.write((uint32_t) 0);
    buffer.write(quest_title);
    buffer.set(0, 3);
    buffer.write(league);
    buffer.set(0, 6);
  }
};

}// namespace openao::game::entity

#endif// OPENAO_GAME_ENTITY_MODEL_CHARACTER_H