#ifndef OPENAO_GAME_MOVEMENT_CONTROLLER_H
#define OPENAO_GAME_MOVEMENT_CONTROLLER_H

#include "transport/iclient.h"

#include "movement/commands/move.h"
#include "movement/events/move.h"
#include "stage/manager.h"

using namespace openao::game::stage;

namespace openao::game::movement {

class Controller {
public:
  static void move(IClient &client, const commands::Move &command,
                   character::Manager &character_manager,
                   stage::Manager &stage_manager,
                   entity::Manager &entity_manager) {
    auto character_id = character_manager.get(&client);
    auto *entity = entity_manager.get(character_id);

    events::Move event;
    event.entity = entity->entityid;
    event.source = {command.source.x, command.source.y};
    event.destination = {command.destination.x, command.destination.y};
    event.speed = 150;

    stage_manager.broadcast(event);

    entity->position.x = command.destination.x / 32;
    entity->position.y = command.destination.y / 32;
  }
};

}// namespace openao::game::movement


#endif// OPENAO_GAME_MOVEMENT_CONTROLLER_H;