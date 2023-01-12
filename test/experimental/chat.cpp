#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "experimental/game/chat/controller.h"

#include "mockclient.h"
#include "mockmessagestream.h"

using namespace openao::experimental::game;
using namespace openao::experimental::game::chat;
using namespace openao::experimental::game::character;
using namespace openao::experimental;


TEST(Chat, Chat_SendChatMessage_Test) {


  // Create connected players
  std::unordered_set<std::unique_ptr<IClient>> players;
  players.emplace(std::make_unique<MockClient>());
  players.emplace(std::make_unique<MockClient>());
  players.emplace(std::make_unique<MockClient>());

  CharacterManager character_manager;

  // Create stage
  Stage stage{character_manager};
  for (auto &client: players) {
    stage.join(*client);

    auto &mock_client = static_cast<MockClient &>(*client);
    EXPECT_CALL(mock_client, send).Times(1);
  }


  // Obtain sender
  auto &sender = (*players.begin()->get());

  // Sent message
  ChatMessageCommand chat_message;
  chat_message.text = "Hello world!";

  // Execution
  ChatController::send_chat_message(sender, chat_message, stage);
}