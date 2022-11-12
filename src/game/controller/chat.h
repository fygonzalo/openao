
#ifndef OPENAO_GAME_CONTROLLER_CHAT_H
#define OPENAO_GAME_CONTROLLER_CHAT_H

#include "game/messages/requests/global_message.h"
#include "game/messages/responses/global_message.h"
#include "game/subsystems/entitymanager.h"
namespace Game::Controller {

class Chat {
public:
  Chat(Subsystems::EntityManager &entityManager)
      : entity_manager_(entityManager) {}

  void global_message(MessageStream &stream,
                                 Messages::Requests::GlobalMessage &request) {

    auto &entity = entity_manager_.find_by_stream(stream);

    Messages::Responses::GlobalMessage gm{.entityid = entity.id,
                                          .nick = entity.character.name,
                                          .message = request.message};

    for (auto &e: entity_manager_.get_all()) { e.stream->write(gm); }
  }

private:
  Subsystems::EntityManager &entity_manager_;
};

}// namespace Game::Controller

#endif// OPENAO_GAME_CONTROLLER_CHAT_H
