
#ifndef OPENAO_EXPERIMENTAL_EVENTS_GAME_MESSAGE_H
#define OPENAO_EXPERIMENTAL_EVENTS_GAME_MESSAGE_H

#include <cstdint>

#include "experimental/events/abstractevent.h"
#include "utils/string.h"

namespace openao::experimental::events::game {

struct Message : AbstractEvent {

  uint32_t entity{0};
  String name{16};
  String text{80};

  void serialize(BinaryBuffer &buffer) const {
    buffer.write(entity);
    buffer.write(name);
    buffer.write(text);
  }

  void deserialize(BinaryBuffer &buffer) {
    buffer.read(entity);
    buffer.read(name);
    buffer.read(text);
  }
};

}// namespace openao::experimental::events::game

#endif// OPENAO_EXPERIMENTAL_EVENTS_GAME_MESSAGE_H
