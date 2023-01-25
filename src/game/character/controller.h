#ifndef OPENAO_GAME_CHARACTER_CONTROLLER_H
#define OPENAO_GAME_CHARACTER_CONTROLLER_H

#include "transport/iclient.h"

#include "character/commands/authenticate.h"
#include "character/commands/interact.h"
#include "character/commands/logout.h"
#include "character/commands/settitle.h"
#include "character/events/characterdetail.h"
#include "character/events/loadfunctionbar.h"
#include "character/events/showemote.h"
#include "character/events/titlechanged.h"

#include "character/irepository.h"
#include "character/manager.h"
#include "entity/events/destroy.h"
#include "entity/manager.h"
#include "inventory/manager.h"
#include "stage/manager.h"

using namespace openao::framework::transport;
using namespace openao::game;
using namespace openao::game::stage;


namespace openao::game::character {

class Controller {
public:
  static void authenticate(IClient &client,
                           const commands::Authenticate &command,
                           character::IRepository &character_repository,
                           character::Manager &character_manager,
                           stage::Manager &stage_manager,
                           entity::Manager &entity_manager) {

    // Validate character command
    auto character = character_repository.get(command.character_id);
    if (auto other = character_manager.get(command.character_id)) {
      other->disconnect();
      client.disconnect();
      return;
    }

    // CREATE PLAYER OWN ENTITY
    auto &entity = entity_manager.create();

    // SELF SPAWN
    character_manager.insert(&client, command.character_id);
    events::CharacterDetail event;
    event.entityid = entity.entityid;
    event.position.x = character.position.x;
    event.position.y = character.position.y;
    event.name = character.name;
    event.title = character.title;
    event.orientation = character.position.orientation;
    event.shape = character.shape;
    event.attributes.gender = character.attributes.gender;
    event.attributes.hair_color = character.attributes.hair_color;
    event.attributes.hair_style = character.attributes.hair_style;
    event.attributes.height = character.attributes.height;
    event.attributes.skin_color = character.attributes.skin_color;
    event.faction = character.faction;
    event.level = character.level;
    event.experience = character.experience;
    event.rank = character.rank;
    event.credits = character.credits;
    event.stats.hp = {character.stats.hp.current, character.stats.hp.total};
    event.stats.mp = {character.stats.mp.current, character.stats.mp.total};
    event.stats.sp = {character.stats.sp.base, character.stats.sp.total};
    event.stats.attack_base = character.stats.attack_base;
    event.stats.attack_right = character.stats.attack_left;
    event.stats.attack_left = character.stats.attack_right;
    event.stats.defense.current = character.stats.defense.current;
    event.stats.defense.total = character.stats.defense.total;
    event.stats.spell_attack.current = character.stats.spell_attack.current;
    event.stats.spell_attack.total = character.stats.spell_attack.total;
    event.stats.spell_defense.current = character.stats.spell_defense.current;
    event.stats.spell_defense.total = character.stats.spell_defense.total;
    event.stats.rigor.base = character.stats.rigor.base;
    event.stats.rigor.total = character.stats.rigor.total;
    event.stats.agility.base = character.stats.agility.base;
    event.stats.agility.total = character.stats.agility.total;
    event.stats.critical.base = character.stats.critical.base;
    event.stats.critical.total = character.stats.critical.total;
    event.stats.stamina.base = character.stats.stamina.base;
    event.stats.stamina.total = character.stats.stamina.total;
    event.stats.soul_defense.base = character.stats.soul_defense.base;
    event.stats.soul_defense.total = character.stats.soul_defense.total;
    event.stats.thunder.attack = character.stats.thunder.attack;
    event.stats.thunder.defense = character.stats.thunder.defense;
    event.stats.fire.attack = character.stats.fire.attack;
    event.stats.fire.defense = character.stats.fire.defense;
    event.stats.ice.attack = character.stats.ice.attack;
    event.stats.ice.defense = character.stats.ice.defense;
    event.stats.rotten.attack = character.stats.rotten.attack;
    event.stats.rotten.defense = character.stats.rotten.defense;
    event.stats.weight = {23132, character.stats.weight.total};
    event.character_id = character.id;
    client.send(event);

    events::LoadFunctionBar function_bar;
    function_bar[0] = events::LoadFunctionBar::Function{3, 19};
    client.send(function_bar);

    // SPAWN ALL THE ENTITIES TO THE PLAYER
    std::list<entity::Character> &entities = entity_manager.get();
    for (entity::Character &e: entities) {
      if (e.entityid != entity.entityid) client.send(e);
    }

    // SPAWN SELF TO OTHERS
    entity.position.x = character.position.x;
    entity.position.y = character.position.y;
    entity.name = character.name;
    entity.title = character.title;
    entity.orientation = character.position.orientation;
    entity.shape = character.shape;
    entity.attributes.gender = character.attributes.gender;
    entity.attributes.hair_color = character.attributes.hair_color;
    entity.attributes.hair_style = character.attributes.hair_style;
    entity.attributes.height = character.attributes.height;
    entity.attributes.skin_color = character.attributes.skin_color;
    entity.faction = character.faction;
    entity.equipment.head = character.equipment.head;
    entity.equipment.body = character.equipment.body;
    entity.equipment.right_hand = character.equipment.right_hand;
    entity.equipment.left_hand = character.equipment.left_hand;
    entity.equipment.hand = character.equipment.hand;
    entity.equipment.feet = character.equipment.feet;
    entity.equipment.back = character.equipment.back;
    entity.equipment.ride = character.equipment.ride;
    entity.character_id = character.id;
    stage_manager.broadcast(entity);

    // SUBSCRIBE TO THE EVENTS
    stage_manager.subscribe(&client);
  }

  static void interact(IClient &client, const commands::Interact &command,
                       character::Manager &character_manager,
                       stage::Manager &stage_manager,
                       entity::Manager &entity_manager) {
    auto character_id = character_manager.get(&client);
    auto *entity = entity_manager.get(character_id);
    if (command.code == 1) {
      events::ShowEmote event;
      event.entity = entity->entityid;
      event.emote = command.entity;
      stage_manager.broadcast(event);
    }
  }

  static void set_title(IClient &client, const commands::SetTitle &command,
                        character::Manager &character_manager,
                        entity::Manager &entity_manager,
                        stage::Manager &stage_manager) {
    auto character_id = character_manager.get(&client);
    auto entity = entity_manager.get(character_id);

    entity->title = command.title;

    events::TitleChanged event;
    event.entity = entity->entityid;
    event.title = command.title;
    stage_manager.broadcast(event);
  }

  static void logout(IClient &client, const commands::Logout &command) {
    client.disconnect();
  }

  static void disconnect(IClient &client,
                         const IClient::ConnectionClosed &command,
                         character::IRepository &character_repository,
                         character::Manager &character_manager,
                         stage::Manager &stage_manager,
                         entity::Manager &entity_manager) {

    auto character_id = character_manager.get(&client);
    if (character_id == -1) return;

    stage_manager.unsubscribe(&client);
    auto entity = entity_manager.get(character_id);
    if (!entity) return;

    model::Character character;
    character.id = character_id;
    character.title = entity->title;
    character.position.x = entity->position.x;
    character.position.y = entity->position.y;
    character.position.orientation = entity->orientation;
    character_repository.save(character);

    entity_manager.remove(character_id);
    character_manager.remove(&client);

    entity::Destroy destroy;
    destroy.entity_id = entity->entityid;
    destroy.reason = 1;
    stage_manager.broadcast(destroy);
  }
};

}// namespace openao::game::character

#endif// OPENAO_GAME_CHARACTER_CHARACTERCONTROLLER_H
