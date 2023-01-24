#ifndef OPENAO_GAME_CHAT_CONTROLLER_H
#define OPENAO_GAME_CHAT_CONTROLLER_H

#include "transport/iclient.h"

#include "chat/commands/say.h"
#include "chat/events/says.h"

#include "character/manager.h"
#include "entity/manager.h"
#include "stage/manager.h"

using namespace openao::framework::transport;

namespace openao::game::chat {

class Controller {
public:
  static void say(IClient &client, const chat::Say &command,
                  character::Manager &character_manager,
                  entity::Manager &entity_manager,
                  stage::Manager &stage_manager) {
    auto character_id = character_manager.get(&client);
    auto entity = entity_manager.get(character_id);

    chat::Says event;
    event.name = entity->name;
    event.entity = entity->entityid;
    event.message = command.message;

    stage_manager.broadcast(event);
  }
};

}// namespace openao::game::chat

#endif// OPENAO_GAME_CHAT_CONTROLLER_H
