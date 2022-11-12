
#ifndef OPENAO_GAME_CONTROLLER_MOVEMENT_H
#define OPENAO_GAME_CONTROLLER_MOVEMENT_H

#include "game/messages/requests/move.h"
#include "game/messages/responses/move.h"
#include "game/subsystems/entitymanager.h"
namespace Game::Controller {

class Movement {

public:
  Movement(Subsystems::EntityManager &entity_manager)
      : entity_manager_(entity_manager){};

  void move(MessageStream &stream,
                       Messages::Requests::Move &request) {
    auto &entity = entity_manager_.find_by_stream(stream);

    Messages::Responses::Move move{
            .entityid = entity.id,
            .source = {.x = request.source.x, .y = request.source.y},
            .destination =
                    {
                            .x = request.destination.x,
                            .y = request.destination.y,
                    },
            .speed = 50,
    };

    for (Subsystems::Entity &e: entity_manager_.get_all()) {
      e.stream->write(move);
    }

    entity.character.position.x = request.destination.x / 32;
    entity.character.position.y = request.destination.y / 32;
  }

private:
  Subsystems::EntityManager &entity_manager_;
};

}// namespace Game::Controller

#endif// OPENAO_GAME_CONTROLLER_MOVEMENT_H
