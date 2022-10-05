
#ifndef OPENAO_GAME_CONTROLLER_ACCOUNT_H
#define OPENAO_GAME_CONTROLLER_ACCOUNT_H

#include "game/messages/requests/auth.h"
#include "game/messages/responses/character.h"
#include "game/messages/responses/loadinventory.h"

#include "transport/messagestream.h"

#include "datasources/icharacter.h"
#include "datasources/iinventory.h"

#include "game/messages/responses/spawnplayer.h"
#include "game/subsystems/inventory.h"

namespace Game::Controller {

class Account {
public:
  Account(Datasources::ICharacter &icharacter,
          Game::Subsystems::Inventory &inventory)
      : character_(icharacter), inventory_(inventory) {}

  awaitable<void> authenticate(MessageStream &stream,
                               Messages::Requests::Auth &request) {
    auto character = character_.get_character_by_id(request.character_id);
    Messages::Responses::Character charinfo{.c = character};
    co_await stream.write(charinfo);

    Messages::Responses::LoadInventory inventory{};
    inventory.items = inventory_.get_inventory(request.character_id);
    co_await stream.write(inventory);


    Messages::Responses::SpawnPlayer sp{.c = character};
    for (auto [s, c] : streams_) {
      co_await s->write(sp);
      Messages::Responses::SpawnPlayer sp_{.c = c};
      co_await stream.write(sp_);
    }

    streams_.emplace_back(&stream, character);

  }

private:
  Datasources::ICharacter &character_;
  Game::Subsystems::Inventory &inventory_;

  std::vector<std::tuple<MessageStream*, Model::Character>> streams_;
};

}// namespace Game::Controller

#endif// OPENAO_GAME_CONTROLLER_ACCOUNT_H
