
#ifndef OPENAO_EXPERIMENTAL_GAME_CHAT_CHATMESSAGEEVENT_H
#define OPENAO_EXPERIMENTAL_GAME_CHAT_CHATMESSAGEEVENT_H

#include "experimental/reactor/event.h"
#include "utils/string.h"
#include <cstdint>

namespace openao::experimental::game::chat {

struct ChatMessageEvent : reactor::IEvent {

  uint32_t entity;
  String name{16};
  std::string text;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(entity);
    buffer.write(name);
    buffer.write(text);
  }
};


}// namespace openao::experimental::game::chat

#endif// OPENAO_EXPERIMENTAL_GAME_CHAT_CHATMESSAGEEVENT_H
