#ifndef OPENAO_GAME_MESSAGES_RESPONSES_POSTAUTHOK_H
#define OPENAO_GAME_MESSAGES_RESPONSES_POSTAUTHOK_H

#include <cstdint>
namespace Game::Messages::Responses {

struct PostAuthOk {
  static const uint16_t type = 322;

  uint8_t code = 0;

  template<typename Archive>
  void serialize(Archive &archive) {
    archive.write(code);
  }
};

}// namespace Game::Messages::Responses

#endif// OPENAO_GAME_MESSAGES_RESPONSES_POSTAUTHOK_H
