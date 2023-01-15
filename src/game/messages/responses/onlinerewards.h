
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_ONLINEREWARDS_H
#define OPENAO_GAME_MESSAGES_RESPONSES_ONLINEREWARDS_H

#include "utils/binarybuffer.h"
#include <cstdint>

namespace Game::Messages::Responses {

struct Test {
  static const uint16_t type = 366;

  void serialize(BinaryBuffer &buffer) {
    buffer.write((uint32_t) 10);
    buffer.write((uint32_t) 0);
    buffer.write((uint32_t) 66374);
    buffer.write((uint32_t) 1);
    buffer.write((uint32_t) 0);
  }
};

}// namespace Game::Messages::Responses

#endif// OPENAO_GAME_MESSAGES_RESPONSES_ONLINEREWARDS_H
