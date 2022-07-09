
#ifndef OPENAO_GAME_SERVICES_ACCOUNT_H
#define OPENAO_GAME_SERVICES_ACCOUNT_H

#include "game/messages/requests/auth.h"
#include "game/messages/responses/character.h"
#include "game/messages/responses/inventory.h"

#include "transport/messagestream.h"

#include "repositories/icharacter.h"


namespace Game::Services {

class Account {
public:
  Account(Repositories::ICharacter &icharacter) : icharacter_(icharacter) {}

  awaitable<void> authenticate(MessageStream &stream,
                               Messages::Requests::Auth &request) {
    auto character = icharacter_.get_character_by_id(request.character_id);
    Messages::Responses::Character response{.c = character};
    co_await stream.write(response);


    Model::BagItem money{.id = 1,
                         .character_id = request.character_id,
                         .slot = 0,
                         .item_id = 1,
                         .quantity = 10000};

    Messages::Responses::Inventory inventory{};
    inventory.items.push_back(money);

    co_await stream.write(inventory);
  }

private:
  Repositories::ICharacter &icharacter_;
};

}// namespace Game::Services

#endif// OPENAO_GAME_SERVICES_ACCOUNT_H
