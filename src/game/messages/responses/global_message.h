
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_GLOBAL_MESSAGE_H
#define OPENAO_GAME_MESSAGES_RESPONSES_GLOBAL_MESSAGE_H

#include "utils/string.h"
namespace Game::Messages::Responses {

struct GlobalMessage {
  static const uint16_t type = 23;

  uint32_t entityid;
  String nick{16};
  String message{80};

  void serialize(BinaryBuffer &buffer) {
    buffer.write(entityid);
    buffer.write(nick);
    buffer.write(message);
  }

  void deserialize(BinaryBuffer& buffer) {
    buffer.read(entityid);
    buffer.read(nick);
    buffer.read(message);
  }

};

}

#endif// OPENAO_GAME_MESSAGES_RESPONSES_GLOBAL_MESSAGE_H
