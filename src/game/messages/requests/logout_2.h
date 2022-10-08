
#ifndef OPENAO_GAME_MESSAGES_REQUESTS_LOGOUT_2_H
#define OPENAO_GAME_MESSAGES_REQUESTS_LOGOUT_2_H

#include <cstdint>

namespace Game::Messages::Requests {

struct Logout2 {
  static const uint16_t type = 17;

  template<typename Archive>
  void deserialize(Archive &archive) {}
};

}// namespace Game::Messages::Requests

#endif// OPENAO_GAME_MESSAGES_REQUESTS_LOGOUT_2_H
