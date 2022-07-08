
#ifndef OPENAO_GAME_MESSAGES_REQUESTS_AUTH_H
#define OPENAO_GAME_MESSAGES_REQUESTS_AUTH_H

#include "utils/binarybuffer.h"
#include <array>
#include <cstdint>
namespace Game {
struct Auth {
  static const uint16_t type = 0x02;

  std::array<uint8_t, 17> interface;
  uint32_t account_id;
  uint32_t character_id;
  uint32_t stage;
  uint32_t session;

  void deserialize(BinaryBuffer& buffer) {
    buffer.read(interface);
    buffer.read(account_id);
    buffer.read(character_id);
    buffer.read(stage);
    buffer.read(session);
  }
};
}

#endif// OPENAO_GAME_MESSAGES_REQUESTS_AUTH_H
