
#ifndef OPENAO_GAME_MESSAGES_REQUESTS_POSTAUTH_H
#define OPENAO_GAME_MESSAGES_REQUESTS_POSTAUTH_H

#include <cstdint>

namespace Game::Messages::Requests {

struct PostAuth {
  static const uint16_t type = 3;

  template<typename Archive>
  void deserialize(Archive &archive) {
  }
};

}

#endif// OPENAO_GAME_MESSAGES_REQUESTS_POSTAUTH_H
