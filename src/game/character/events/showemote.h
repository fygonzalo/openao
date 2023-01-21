#ifndef OPENAO_GAME_CHARCTER_EVENTS_SHOWEMOTE_H
#define OPENAO_GAME_CHARCTER_EVENTS_SHOWEMOTE_H

#include "event.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;

namespace openao::game::character::events {

struct ShowEmote : framework::IEvent {

  uint32_t entity;
  uint8_t emote;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(entity);
    buffer.write(emote);
  }
};

}// namespace openao::game::character::events

#endif// OPENAO_GAME_CHARCTER_EVENTS_SHOWEMOTE_H