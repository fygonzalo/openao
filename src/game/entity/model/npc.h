#ifndef OPENAO_GAME_ENTITY_MODEL_NPC_H
#define OPENAO_GAME_ENTITY_MODEL_NPC_H

#include "event.h"
#include "utils/binarybuffer.h"
#include "utils/string.h"
#include <cstdint>

using namespace openao::framework::utils;

namespace openao::game::entity {

struct NPC : framework::IEvent {
  struct Position {
    uint32_t x;
    uint32_t y;

    void serialize(BinaryBuffer &buffer) {
      buffer.write(x);
      buffer.write(y);
    }
  };

  uint32_t id;
  uint32_t tag{1};
  Position position;
  String name{16};
  uint8_t orientation;
  uint32_t model;
  uint16_t faction;
  uint32_t level;
  uint32_t type;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(id);
    buffer.write(tag);
    buffer.write(position);
    buffer.write(name);
    buffer.write(orientation);
    buffer.write(model);
    buffer.write(faction);
    buffer.write(level);
    buffer.write((uint16_t) 0);
    buffer.write(type);
    buffer.set(0, 12);
  }
};

}// namespace openao::game::entity
#endif// OPENAO_GAME_ENTITY_MODEL_NPC_H
