
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_SET_TIMESTAMP_H
#define OPENAO_GAME_MESSAGES_RESPONSES_SET_TIMESTAMP_H

#include "utils/binarybuffer.h"
#include <cstdint>
namespace Game::Messages::Responses {

struct SetTimestamp {

  static const uint16_t type = 93;

  uint32_t timestamp;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(timestamp);
  }

};

}

#endif// OPENAO_GAME_MESSAGES_RESPONSES_SET_TIMESTAMP_H
