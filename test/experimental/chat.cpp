#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "experimental/game/chat/controller.h"

#include "messagestreammock.h"

using namespace openao::experimental::game;
using namespace openao::experimental::game::chat;
using namespace openao::experimental::game::character;
using namespace openao::experimental;


TEST(Chat, Chat_SendChatMessage_Test) {

  Serializer serializer;
  serializer.insert<ChatMessageEvent>(23);

  // Create connected players
  std::unordered_set<std::unique_ptr<Client>> players;
  players.emplace(std::make_unique<Client>(std::make_unique<MessageStreamMock>(), serializer));
  players.emplace(std::make_unique<Client>(std::make_unique<MessageStreamMock>(), serializer));
  players.emplace(std::make_unique<Client>(std::make_unique<MessageStreamMock>(), serializer));

  CharacterManager character_manager;

  // Create stage
  Stage stage{character_manager};
  for (auto& client : players) {
    stage.join(*client);

    auto& mock_stream = static_cast<MessageStreamMock&>(client->stream());
    EXPECT_CALL(mock_stream, send).Times(1);
  }


  // Obtain sender
  auto& sender = (*players.begin()->get());

  // Sent message
  ChatMessageCommand chat_message;
  chat_message.text = "Hello world!";

  // Execution
  ChatController::send_chat_message(sender, chat_message, stage);
}