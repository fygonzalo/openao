
#ifndef OPENAO_LOGIN_MESSAGES_REQUESTS_ENTER_GAME_H
#define OPENAO_LOGIN_MESSAGES_REQUESTS_ENTER_GAME_H

#include "utils/binarybuffer.h"
#include "utils/string.h"
#include <cstdint>

namespace Login::Messages::Requests {

struct EnterGame {

  static const uint16_t type = 6;

  uint8_t unk_1;
  uint8_t branch;
  String pin{32};

  void deserialize(BinaryBuffer &buffer) {
    buffer.read(unk_1);
    buffer.read(branch);
    buffer.read(pin);
  }
};

}// namespace Login::Messages::Requests

#endif// OPENAO_LOGIN_MESSAGES_REQUESTS_ENTER_GAME_H
