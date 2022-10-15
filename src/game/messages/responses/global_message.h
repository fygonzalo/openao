
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_GLOBAL_MESSAGE_H
#define OPENAO_GAME_MESSAGES_RESPONSES_GLOBAL_MESSAGE_H

#include "utils/string.h"
namespace Game::Messages::Responses {

struct GlobalMessage {
  static const uint16_t type = 23;

  uint32_t entityid;
  String nick{16};
  String message{80};

  template<typename Archive>
  void serialize(Archive &archive) {
    archive.write(entityid);
    archive.write(nick);
    archive.write(message);
  }

};

}

#endif// OPENAO_GAME_MESSAGES_RESPONSES_GLOBAL_MESSAGE_H
