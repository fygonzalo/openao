
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_TEST_H
#define OPENAO_GAME_MESSAGES_RESPONSES_TEST_H

#include "utils/binarybuffer.h"
#include <cstdint>

namespace Game::Messages::Responses {

struct Test {
  static const uint16_t type = 92;

  uint32_t entity;
  uint8_t action;

  void serialize(BinaryBuffer &buffer) {
    uint8_t data[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                      0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
                      0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00};

    buffer.write((char *) data, sizeof(data));
  }
};

}// namespace Game::Messages::Responses

#endif// OPENAO_GAME_MESSAGES_RESPONSES_TEST_H
