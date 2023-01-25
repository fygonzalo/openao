#ifndef OPENAO_GAME_ENTITY_EVENTS_UPDATE_H
#define OPENAO_GAME_ENTITY_EVENTS_UPDATE_H

#include <vector>

#include "event.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;

namespace openao::game::entity::events {

struct Update : framework::IEvent {

  struct Event {
    uint8_t code;
    uint32_t first;
    uint32_t second;

    void serialize(BinaryBuffer &buffer) {
      buffer.write(code);
      buffer.write(first);
      buffer.write(second);
    }
  };

  uint32_t entity;
  std::vector<Update::Event> events;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(entity);
    buffer.write((uint8_t) events.size());
    buffer.write(events);
  }
};

}// namespace openao::game::entity::events

#endif// OPENAO_GAME_ENTITY_EVENTS_UPDATE_H
