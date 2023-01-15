
#ifndef OPENAO_GAME_MESSAGES_REQUESTS_INTERACT_H
#define OPENAO_GAME_MESSAGES_REQUESTS_INTERACT_H

#include <cstdint>
namespace Game::Messages::Requests {

struct Interact {
  static const uint16_t type = 22;

  uint8_t code;
  uint32_t entity;

  template<typename Archive>
  void deserialize(Archive &archive) {
    archive.read(code);
    archive.read(entity);
  }
};

}// namespace Game::Messages::Requests

#endif// OPENAO_GAME_MESSAGES_REQUESTS_INTERACT_H
