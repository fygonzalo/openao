
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_AFTER_SPAWNPLAYER_H
#define OPENAO_GAME_MESSAGES_RESPONSES_AFTER_SPAWNPLAYER_H

#include "utils/binarybuffer.h"
#include <cstdint>

namespace Game::Messages::Responses {

struct AfterSpawnPlayer {
  static const uint16_t type = 389;
  uint32_t entity_id;

  void serialize(BinaryBuffer &buffer) {
    buffer.write((uint32_t) entity_id);
    buffer.write((uint32_t) 0);
    buffer.write((uint32_t) 0);
  }
};

}// namespace Game::Messages::Responses

#endif// OPENAO_GAME_MESSAGES_RESPONSES_AFTER_SPAWNPLAYER_H
