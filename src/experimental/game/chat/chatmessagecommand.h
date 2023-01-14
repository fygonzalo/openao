
#ifndef OPENAO_EXPERIMENTAL_GAME_CHAT_CHATMESSAGECOMMAND_H
#define OPENAO_EXPERIMENTAL_GAME_CHAT_CHATMESSAGECOMMAND_H

#include "experimental/reactor/event.h"
#include "utils/string.h"

namespace openao::experimental::game::chat {

struct ChatMessageCommand : reactor::IEvent {

  String text{80};

  void deserialize(BinaryBuffer &buffer) { buffer.read(text); }
};

}// namespace openao::experimental::game::chat

#endif// OPENAO_EXPERIMENTAL_GAME_CHAT_CHATMESSAGECOMMAND_H
