
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_HOUSEINFO_H
#define OPENAO_GAME_MESSAGES_RESPONSES_HOUSEINFO_H

#include "utils/binarybuffer.h"
#include <cstdint>

namespace Game::Messages::Responses {

struct Test {
  static const uint16_t type = 329;

  uint32_t level;
  uint32_t visitors;
  uint32_t magic;
  uint32_t next_level_magic;
  uint32_t place;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(level);
    buffer.write(magic);
    buffer.write(next_level_magic);
    buffer.write(place);
    buffer.write((uint32_t)6);
    buffer.write((uint32_t)0);
    buffer.write((uint32_t)0);
    buffer.write(visitors);
    buffer.write((uint32_t)16776965);

  }

};

}

#endif// OPENAO_GAME_MESSAGES_RESPONSES_HOUSEINFO_H
