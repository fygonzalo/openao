
#ifndef OPENAO_GAME_MESSAGES_REQUESTS_LOGOUT_1_H
#define OPENAO_GAME_MESSAGES_REQUESTS_LOGOUT_1_H

#include <cstdint>

namespace Game::Messages::Requests {

struct Logout1 {
  static const uint16_t type = 313;

  template<typename Archive>
  void deserialize(Archive &archive) {}
};

}// namespace Game::Messages::Requests

#endif// OPENAO_GAME_MESSAGES_REQUESTS_LOGOUT_1_H
