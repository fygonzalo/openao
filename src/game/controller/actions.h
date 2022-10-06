
#ifndef OPENAO_GAME_CONTROLLER_ACTIONS_H
#define OPENAO_GAME_CONTROLLER_ACTIONS_H

#include "game/subsystems/entitymanager.h"
#include "game/messages/requests/interact.h"
#include "game/messages/responses/postauthok.h"
namespace Game::Controller {

class Actions {
public:
  Actions(Subsystems::EntityManager &entityManager)
      : entity_manager_(entityManager) {}

  awaitable<void> execute(MessageStream &stream,
                           Messages::Requests::Interact &request) {
    Messages::Responses::PostAuthOk pao{};
    co_await stream.write(pao);
  }

private:
  Subsystems::EntityManager &entity_manager_;

};

}

#endif// OPENAO_GAME_CONTROLLER_ACTIONS_H
