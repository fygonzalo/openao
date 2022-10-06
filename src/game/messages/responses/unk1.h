
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_UNK1_H
#define OPENAO_GAME_MESSAGES_RESPONSES_UNK1_H

#include <cstdint>
namespace Game::Messages::Responses {

struct Unk1 {
  static const uint16_t type = 20;

  uint32_t entityid;

  template <typename Archive>
  void serialize(Archive& archive) {
    archive.write(entityid);
    archive.set(5, 1);
    archive.set(0, 2);
  }
};

}

#endif// OPENAO_GAME_MESSAGES_RESPONSES_UNK1_H
