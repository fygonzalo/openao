
#ifndef OPENAO_GAME_SERVICES_ACCOUNT_H
#define OPENAO_GAME_SERVICES_ACCOUNT_H

#include "game/messages/requests/auth.h"
#include "game/messages/responses/character.h"
#include "game/messages/responses/inventory.h"

#include "transport/messagestream.h"

#include "repositories/icharacter.h"
#include "repositories/iinventory.h"


namespace Game::Services {

class Account {
public:
  Account(Repositories::ICharacter &icharacter,
          Repositories::IInventory &iinventory)
      : icharacter_(icharacter), iinventory_(iinventory) {}

  awaitable<void> authenticate(MessageStream &stream,
                               Messages::Requests::Auth &request) {
    auto character = icharacter_.get_character_by_id(request.character_id);
    Messages::Responses::Character response{.c = character};
    co_await stream.write(response);

    Messages::Responses::Inventory inventory{};
    inventory.items = iinventory_.get_bag_items(request.character_id);

    co_await stream.write(inventory);
  }

private:
  Repositories::ICharacter &icharacter_;
  Repositories::IInventory &iinventory_;
};

}// namespace Game::Services

#endif// OPENAO_GAME_SERVICES_ACCOUNT_H
