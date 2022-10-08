
#ifndef OPENAO_GAME_CONTROLLER_ACCOUNT_H
#define OPENAO_GAME_CONTROLLER_ACCOUNT_H

#include "game/messages/requests/auth.h"
#include "game/messages/responses/character.h"
#include "game/messages/responses/loadinventory.h"

#include "transport/messagestream.h"

#include "datasources/icharacter.h"
#include "datasources/iinventory.h"

#include "game/messages/requests/postauth.h"
#include "game/messages/responses/postauthok.h"
#include "game/messages/responses/spawnplayer.h"
#include "game/messages/responses/unk1.h"
#include "game/messages/responses/unk2.h"
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
    auto items = inventory_.get_bag_items(request.character_id);

    Subsystems::Entity player{.stream = &stream,
                              .character = character,
                              .items = items};
    entity_manager_.insert(player);

    co_return;
  }

  awaitable<void> postauth(MessageStream &stream,
                           Messages::Requests::PostAuth &request) {
    Subsystems::Entity &entity = entity_manager_.find_by_stream(stream);

    Messages::Responses::PostAuthOk pao{};
    co_await stream.write(pao);

    Messages::Responses::Character charinfo{.entityid = entity.id,
                                            .c = entity.character};
    co_await stream.write(charinfo);

    Messages::Responses::LoadInventory inventory{.items = entity.items};
    co_await stream.write(inventory);

    Messages::Responses::Unk1 unk1{.entityid = entity.id};
    co_await stream.write(unk1);

    Messages::Responses::Unk2 unk2{.entityid = entity.id};
    co_await stream.write(unk2);

    Messages::Responses::SpawnPlayer sp{.entityid = entity.id,
                                        .c = entity.character};

    for (auto e: entity_manager_.get_all()) {
      if (e.id != entity.id) {
        co_await e.stream->write(sp);
        Messages::Responses::SpawnPlayer sp_{.entityid = e.id,
                                             .c = e.character};
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
