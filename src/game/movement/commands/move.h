#ifndef OPENAO_GAME_MOVEMENT_COMMANDS_MOVE_H
#define OPENAO_GAME_MOVEMENT_COMMANDS_MOVE_H

#include "event.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;

namespace openao::game::movement::commands {

struct Move : framework::IEvent {

  struct Position {
    uint16_t x;
    uint16_t y;

    void deserialize(BinaryBuffer &buffer) {
      buffer.read(x);
      buffer.read(y);
    }
  };

  Position source;
  Position destination;

  void deserialize(BinaryBuffer &buffer) {
    buffer.read(source);
    buffer.skip(3);
    buffer.read(destination);
  }
};

}// namespace openao::game::movement::commands

#endif// OPENAO_GAME_MOVEMENT_COMMANDS_MOVE_H