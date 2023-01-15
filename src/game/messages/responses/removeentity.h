
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_REMOVEENTITY_H
#define OPENAO_GAME_MESSAGES_RESPONSES_REMOVEENTITY_H

#include <cstdint>
namespace Game::Messages::Responses {

struct RemoveEntity {
  static const uint16_t type = 7;

  uint32_t entityid;
  uint8_t code;

  template<typename Archive>
  void serialize(Archive &archive) {
    archive.write(entityid);
    archive.write(code);
  }
};

}// namespace Game::Messages::Responses

#endif// OPENAO_GAME_MESSAGES_RESPONSES_REMOVEENTITY_H
