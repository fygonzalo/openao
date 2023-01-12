
#ifndef OPENAO_EXPERIMENTAL_GAME_CHAT_CONTROLLER_H
#define OPENAO_EXPERIMENTAL_GAME_CHAT_CONTROLLER_H

#include <functional>
#include <unordered_set>

#include "experimental/transport/iclient.h"
#include "experimental/game/chat/chatmessageevent.h"
#include "experimental/game/chat/chatmessagecommand.h"

#include "experimental/game/stage.h"


namespace openao::experimental::game::chat {

class ChatController {
public:
  static void send_chat_message(IClient &client,
                                const ChatMessageCommand &command, Stage& stage) {
    ChatMessageEvent chat_event{};
    chat_event.entity = 1;
    chat_event.name = "openao";
    chat_event.text = command.text;

    stage.broadcast(chat_event);
  }
};

}// namespace openao::experimental::game::chat

#endif// OPENAO_EXPERIMENTAL_GAME_CHAT_CONTROLLER_H
