
#ifndef OPENAO_EXPERIMENTAL_GAME_CHAT_CHATMESSAGECOMMAND_H
#define OPENAO_EXPERIMENTAL_GAME_CHAT_CHATMESSAGECOMMAND_H

#include "utils/string.h"
#include "experimental/reactor/event.h"

namespace openao::experimental::game::chat {

struct ChatMessageCommand : reactor::Event<ChatMessageCommand> {

  String text{80};

  void deserialize(BinaryBuffer& buffer) {
    buffer.read(text);
  }

};

}

#endif// OPENAO_EXPERIMENTAL_GAME_CHAT_CHATMESSAGECOMMAND_H
