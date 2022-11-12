
#ifndef OPENAO_GAME_CONTROLLER_ACCOUNT_H
#define OPENAO_GAME_CONTROLLER_ACCOUNT_H

#include "game/messages/requests/auth.h"
#include "game/messages/responses/character.h"
#include "game/messages/responses/loadinventory.h"

#include "transport/messagestream.h"

#include "datasources/icharacter.h"
#include "datasources/iinventory.h"

#include "game/messages/requests/logout_1.h"
#include "game/messages/requests/logout_2.h"
#include "game/messages/requests/postauth.h"
#include "game/messages/responses/postauthok.h"
#include "game/messages/responses/spawnplayer.h"
#include "game/messages/responses/removeentity.h"
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

  void preauth(MessageStream &stream,
                          Messages::Requests::Auth &request) {
    auto character = character_.get_character_by_id(request.character_id);
    auto items = inventory_.get_bag_items(request.character_id);

    Subsystems::Entity player{.stream = &stream,
                              .character = character,
                              .items = items};
    entity_manager_.insert(player);

  }

  void postauth(MessageStream &stream,
                           Messages::Requests::PostAuth &request) {
    Subsystems::Entity &entity = entity_manager_.find_by_stream(stream);

    Messages::Responses::PostAuthOk pao{};
    stream.write(pao);

    Messages::Responses::Character charinfo{.entityid = entity.id,
                                            .c = entity.character};
    stream.write(charinfo);

    Messages::Responses::LoadInventory inventory{.items = entity.items};
    stream.write(inventory);

    Messages::Responses::Unk1 unk1{.entityid = entity.id};
    stream.write(unk1);

    Messages::Responses::Unk2 unk2{.entityid = entity.id};
    stream.write(unk2);

    Messages::Responses::SpawnPlayer sp{.entityid = entity.id,
                                        .c = entity.character};

    for (auto e: entity_manager_.get_all()) {
      if (e.id != entity.id) {
        e.stream->write(sp);
        Messages::Responses::SpawnPlayer sp_{.entityid = e.id,
                                             .c = e.character};
        stream.write(sp_);
      }
    }

  }

  awaitable<void> logout(MessageStream &stream,
                          Messages::Requests::Logout1 &request) {

    auto& e = entity_manager_.find_by_stream(stream);
    auto message = co_await e.stream->read();
    uint32_t eid = e.id;
    auto mi = message.read<Game::Messages::Requests::Logout2>();

    character_.update_character(e.character);
    entity_manager_.remove_by_stream(stream);

    Messages::Responses::RemoveEntity re{.entityid = eid, .code = 0};
    for (auto &e: entity_manager_.get_all()) {
      e.stream->write(re);
    }
  }

private:
  Datasources::ICharacter &character_;
  Datasources::IInventory &inventory_;
  Subsystems::EntityManager &entity_manager_;

};

}// namespace Game::Controller

#endif// OPENAO_GAME_CONTROLLER_ACCOUNT_H
