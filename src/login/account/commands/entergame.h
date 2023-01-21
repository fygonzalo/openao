#ifndef OPENAO_LOGIN_ACCOUNT_COMMANDS_ENTERGAME_H
#define OPENAO_LOGIN_ACCOUNT_COMMANDS_ENTERGAME_H

#include <cstdint>

#include "event.h"
#include "utils/binarybuffer.h"
#include "utils/string.h"

using namespace openao::framework::utils;

namespace openao::login::account::commands {

struct EnterGame : framework::IEvent {
  uint8_t character_index;
  uint8_t branch;
  String pin{32};

  void deserialize(BinaryBuffer &buffer) {
    buffer.read(character_index);
    buffer.read(branch);
    buffer.read(pin);
  }
};

}// namespace openao::login::account::commands

#endif// OPENAO_LOGIN_ACCOUNT_COMMANDS_ENTERGAME_H
