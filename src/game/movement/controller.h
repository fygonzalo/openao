#ifndef OPENAO_GAME_MOVEMENT_CONTROLLER_H
#define OPENAO_GAME_MOVEMENT_CONTROLLER_H

#include "transport/iclient.h"

#include "movement/commands/move.h"
#include "movement/events/move.h"

namespace openao::game::movement {

class Controller {
public:
  static void move(IClient &client, const commands::Move &command) {

    events::Move event;
    event.entity = 1;
    event.source = {command.source.x, command.source.y};
    event.destination = {command.destination.x, command.destination.y};
    event.speed = 150;

    client.send(event);
  }
};

}// namespace openao::game::movement


#endif// OPENAO_GAME_MOVEMENT_CONTROLLER_H;