#ifndef OPENAO_GAME_CHARACTER_EVENTS_TITLECHANGED_H
#define OPENAO_GAME_CHARACTER_EVENTS_TITLECHANGED_H

#include "event.h"
#include <cstdint>

#include "utils/binarybuffer.h"
#include "utils/string.h"

using namespace openao::framework::utils;

namespace openao::game::character::events {

struct TitleChanged : framework::IEvent {

  uint32_t entity;
  String title{16};

  void serialize(BinaryBuffer &buffer) {
    buffer.write(entity);
    buffer.write((uint8_t) 1);
    buffer.write(title);
  }
};


};// namespace openao::game::character::events

#endif// OPENAO_GAME_CHARACTER_EVENTS_TITLECHANGED_H
