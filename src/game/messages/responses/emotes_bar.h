
#ifndef OPENAO_EMOTES_BAR_H
#define OPENAO_EMOTES_BAR_H


#ifndef OPENAO_GAME_MESSAGES_RESPONSES_TEST_H
#define OPENAO_GAME_MESSAGES_RESPONSES_TEST_H

#include "utils/binarybuffer.h"
#include <cstdint>

namespace Game::Messages::Responses {

struct Test {
  static const uint16_t type = 29;

  void serialize(BinaryBuffer &buffer) {
    buffer.write((uint32_t)1);
    buffer.write((uint8_t)8);
    // Load emote
    buffer.write((uint8_t)6);
    // Position
    buffer.write((uint32_t)0);
    // Emote
    buffer.write((uint32_t)0x13);

    for (int i = 1; i < 4; i++) {
      buffer.write((uint8_t)6);
      buffer.write((uint32_t)i);
      buffer.write((uint32_t)0xffffffff);
    }

    buffer.write((uint8_t)7);
    buffer.write((uint32_t)0);
    buffer.write((uint32_t)32799);

    buffer.write((uint8_t)7);
    buffer.write((uint32_t)1);
    buffer.write((uint32_t)32792);

    buffer.write((uint8_t)7);
    buffer.write((uint32_t)2);
    buffer.write((uint32_t)32800);

    buffer.write((uint8_t)7);
    buffer.write((uint32_t)3);
    buffer.write((uint32_t)32896);
  }

};

}

#endif// OPENAO_GAME_MESSAGES_RESPONSES_TEST_H


#endif// OPENAO_EMOTES_BAR_H
