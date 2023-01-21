#ifndef OPENAO_GAME_CHARACTER_EVENTS_LOADFUNCTIONBAR_H
#define OPENAO_GAME_CHARACTER_EVENTS_LOADFUNCTIONBAR_H


#include <array>

#include "event.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;

namespace openao::game::character::events {

struct LoadFunctionBar : framework::IEvent {

  struct Function {

    // 0, unset, 1 spell, 2 consumable, 3 emote, 4 item
    uint8_t type;
    // id of the object of type ^
    uint32_t reference;

    void serialize(BinaryBuffer &buffer) {
      buffer.write(type);
      buffer.write(reference);
      buffer.write((uint32_t) 0);
    }
  };

  Function &operator[](int index) { return functions[index]; }

  std::array<Function, 24> functions;

  void serialize(BinaryBuffer &buffer) { buffer.write(functions); }
};

}// namespace openao::game::character::events

#endif// GAME_CHARACTER_EVENTS_LOADFUNCTIONBAR_H