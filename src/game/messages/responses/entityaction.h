
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_ENTITYACTION_H
#define OPENAO_GAME_MESSAGES_RESPONSES_ENTITYACTION_H

#include <cstdint>
namespace Game::Messages::Responses {

struct EntityAction {

  static const uint16_t type = 29;

  uint32_t entity;
  uint8_t action = 1;
  uint32_t slot;
  uint32_t code;

  template<typename Archive>
  void serialize(Archive &archive) {
    archive.write(entity);
    archive.set(1, 1);
    archive.write(action);
    archive.write(slot);
    archive.write(code);
  }

};

}

#endif// OPENAO_GAME_MESSAGES_RESPONSES_ENTITYACTION_H
