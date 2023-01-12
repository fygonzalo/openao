
#ifndef OPENAO_EXPERIMENTAL_GAME_CHAT_CHATMESSAGEEVENT_H
#define OPENAO_EXPERIMENTAL_GAME_CHAT_CHATMESSAGEEVENT_H

#include "utils/string.h"
#include <cstdint>


namespace openao::experimental::game::chat {

struct ChatMessageEvent {

  uint32_t entity;
  String name{12};
  String text{80};

  void serialize(BinaryBuffer &buffer) {
    buffer.write(entity);
    buffer.write(name);
    buffer.write(text);
  }

};


}// namespace openao::experimental::game::chat

#endif// OPENAO_EXPERIMENTAL_GAME_CHAT_CHATMESSAGEEVENT_H
