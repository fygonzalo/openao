
#ifndef OPENAO_GAME_CONTROLLER_ACTIONS_H
#define OPENAO_GAME_CONTROLLER_ACTIONS_H

#include "game/messages/requests/interact.h"
#include "game/messages/responses/postauthok.h"
#include "game/subsystems/entitymanager.h"
namespace Game::Controller {

class Actions {
public:
  Actions(Subsystems::EntityManager &entityManager)
      : entity_manager_(entityManager) {}

  void execute(MessageStream &stream, Messages::Requests::Interact &request) {
    Messages::Responses::PostAuthOk pao{};
    stream.write(pao);
  }

private:
  Subsystems::EntityManager &entity_manager_;
};

}// namespace Game::Controller

#endif// OPENAO_GAME_CONTROLLER_ACTIONS_H
