#ifndef OPENAO_GAME_MOVEMENT_EVENTS_MOVE_H
#define OPENAO_GAME_MOVEMENT_EVENTS_MOVE_H

#include "event.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;

namespace openao::game::movement::events {

struct Move : framework::IEvent {
  struct Position {
    uint32_t x;
    uint32_t y;

    void serialize(BinaryBuffer &buffer) {
      buffer.write(x);
      buffer.write(y);
    }
  };

  uint32_t entity;
  Position source;
  Position destination;
  uint16_t speed;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(entity);
    buffer.write(source);
    buffer.write(destination);
    buffer.write(speed);
  }
};

}// namespace openao::game::movement::events

#endif// OPENAO_GAME_MOVEMENT_EVENTS_MOVE_H