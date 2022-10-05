
#ifndef OPENAO_GAME_CONTROLLER_ACCOUNT_H
#define OPENAO_GAME_CONTROLLER_ACCOUNT_H

#include "game/messages/requests/auth.h"
#include "game/messages/responses/character.h"
#include "game/messages/responses/loadinventory.h"

#include "transport/messagestream.h"

#include "datasources/icharacter.h"
#include "datasources/iinventory.h"

#include "game/messages/responses/spawnplayer.h"
#include "game/subsystems/entitymanager.h"
#include "game/subsystems/inventory.h"

namespace Game::Controller {

class Account {
public:
  Account(Datasources::ICharacter &icharacter,
          Datasources::IInventory &inventory,
          Subsystems::EntityManager &entity_manager)
      : character_(icharacter), inventory_(inventory),
        entity_manager_(entity_manager) {}

  awaitable<void> preauth(MessageStream &stream,
                               Messages::Requests::Auth &request) {
    auto character = character_.get_character_by_id(request.character_id);
    Messages::Responses::Character charinfo{.c = character};
    co_await stream.write(charinfo);

    Messages::Responses::LoadInventory inventory{};
    auto items = inventory_.get_bag_items(request.character_id);
    inventory.items = items;
    co_await stream.write(inventory);

    Subsystems::Entity player{.stream = &stream,
                              .character = character,
                              .items = items};
    entity_manager_.insert(player);

    Messages::Responses::SpawnPlayer sp{
            .entityid = player.id,
            .c = character};

    for (auto e: entity_manager_.get_all()) {
      if (e.id != player.id) {
        co_await e.stream->write(sp);
        Messages::Responses::SpawnPlayer sp_{.entityid = e.id, .c = e.character};
        co_await stream.write(sp_);
      }
    }
  }

private:
  Datasources::ICharacter &character_;
  Datasources::IInventory &inventory_;
  Subsystems::EntityManager &entity_manager_;

  std::vector<std::tuple<MessageStream *, Model::Character>> streams_;
};

}// namespace Game::Controller

#endif// OPENAO_GAME_CONTROLLER_ACCOUNT_H
