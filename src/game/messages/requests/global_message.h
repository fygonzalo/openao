
#ifndef OPENAO_GAME_MESSAGES_REQUESTS_GLOBAL_MESSAGE_H
#define OPENAO_GAME_MESSAGES_REQUESTS_GLOBAL_MESSAGE_H

#include "utils/string.h"
#include <cstdint>
namespace Game::Messages::Requests {

struct GlobalMessage {

  static const uint16_t type = 14;

  String message{80};

  template<typename Archive>
  void deserialize(Archive &archive) {
    archive.read(message);
  }

};

}

#endif// OPENAO_GAME_MESSAGES_REQUESTS_GLOBAL_MESSAGE_H
