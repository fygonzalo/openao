
#include <gtest/gtest.h>

#include "experimental/ecs/componentmanager.h"

using namespace openao::experimental::ecs;

struct Character {
  uint32_t id;
  std::string name;
};

TEST(ECS, Usage) {

  EntityManager entity_manager;
  ComponentManager component_manager;

  auto player = entity_manager.create();
  Character character{.id = 10, .name = "gonzalo"};

  component_manager.add(player, character);

  auto &c = component_manager.get<Character>(player);
  std::cout << c.name << std::endl;
}

#include "experimental/game/chat/controller.h"
using namespace openao::experimental::game::chat;

TEST(ECS, ChatController_SendChatMessage_Test) {
  Entity entity = 1;

  ChatMessageCommand command;
  command.text = "Hello world";

  std::string name = "gonzalo";


  // ChatController::send_chat_message(entity, command, name, client);
}

void test(int a){

};

TEST(ECS, ChatController_StaticProcess_Test) {
  EntityManager entity_manager;
  ComponentManager component_manager;

  auto entity = entity_manager.create();
  auto name = std::string("gonzalo");
  component_manager.add(entity, name);
  component_manager.add(entity, 5);

  ChatMessageCommand command;
  command.text = "Hello world";
}
