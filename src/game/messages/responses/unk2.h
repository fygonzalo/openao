
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_UNK2_H
#define OPENAO_GAME_MESSAGES_RESPONSES_UNK2_H

#include <cstdint>
namespace Game::Messages::Responses {

struct Unk2 {
  static const uint16_t type = 389;

  uint32_t entityid;

  template <typename Archive>
  void serialize(Archive& archive) {
    archive.write(entityid);
    archive.set(0, 8);
  }
};

}

#endif// OPENAO_GAME_MESSAGES_RESPONSES_UNK2_H
