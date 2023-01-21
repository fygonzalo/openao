#ifndef OPENAO_GAME_CHARACTER_COMMANDS_INTERACT_H
#define OPENAO_GAME_CHARACTER_COMMANDS_INTERACT_H

#include "event.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;

namespace openao::game::character::commands {

struct Interact : framework::IEvent {

  uint8_t code;
  uint32_t entity;

  void deserialize(BinaryBuffer &buffer) {
    buffer.read(code);
    buffer.read(entity);
  }
};


}// namespace openao::game::character::commands


#endif// OPENAO_GAME_CHARACTER_COMMANDS_INTERACT_H