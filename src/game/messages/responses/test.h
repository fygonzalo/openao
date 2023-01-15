
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_TEST_H
#define OPENAO_GAME_MESSAGES_RESPONSES_TEST_H

#include "utils/binarybuffer.h"
#include <cstdint>

namespace Game::Messages::Responses {

struct Test {
  static const uint16_t type = 367;


  void serialize(BinaryBuffer &buffer) {

    uint8_t first[] = {0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
                       0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01,
                       0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00};


    buffer.write((char *) first, sizeof(first));
    // buffer.set(0x01, 37);
  }
};

}// namespace Game::Messages::Responses

#endif// OPENAO_GAME_MESSAGES_RESPONSES_TEST_H
