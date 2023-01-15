
#ifndef OPENAO_GAME_MESSAGES_REQUESTS_GLOBAL_MESSAGE_H
#define OPENAO_GAME_MESSAGES_REQUESTS_GLOBAL_MESSAGE_H

#include "utils/string.h"
#include <cstdint>
namespace Game::Messages::Requests {

struct GlobalMessage {

  static const uint16_t type = 14;

  String message{80};

  void deserialize(BinaryBuffer &archive) { archive.read(message); }
};

}// namespace Game::Messages::Requests

#endif// OPENAO_GAME_MESSAGES_REQUESTS_GLOBAL_MESSAGE_H
