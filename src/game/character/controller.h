#ifndef OPENAO_GAME_CHARACTER_CONTROLLER_H
#define OPENAO_GAME_CHARACTER_CONTROLLER_H

#include "transport/iclient.h"

#include "character/commands/authenticate.h"
#include "character/commands/interact.h"
#include "character/commands/logout.h"
#include "character/events/characterdetail.h"
#include "character/events/loadfunctionbar.h"
#include "character/events/showemote.h"

#include "character/irepository.h"
#include "character/manager.h"

using namespace openao::framework::transport;
using namespace openao::game::character;


namespace openao::game::character {

class Controller {
public:
  static void authenticate(IClient &client,
                           const commands::Authenticate &command,
                           IRepository &character_repository,
                           Manager &character_manager) {

    // Validate character command
    auto character = character_repository.get(command.character_id);
    if (auto other = character_manager.get(command.character_id)) {
      other->disconnect();
      client.disconnect();
      return;
    }

    character_manager.insert(&client, character.id);

    events::CharacterDetail event;

    event.entityid = 1;
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
    event.stats.defense = {character.stats.defense.current,
                           character.stats.defense.total};
    event.stats.spell_attack = {character.stats.spell_attack.current,
                                character.stats.spell_attack.total};
    event.stats.spell_defense = {character.stats.spell_defense.current,
                                 character.stats.spell_defense.total};
    event.stats.rigor = {character.stats.rigor.base,
                         character.stats.rigor.total};
    event.stats.agility = {character.stats.agility.base,
                           character.stats.agility.total};
    event.stats.critical = {character.stats.critical.base,
                            character.stats.critical.total};
    event.stats.stamina = {character.stats.stamina.base,
                           character.stats.stamina.total};
    event.stats.soul_defense = {character.stats.soul_defense.base,
                                character.stats.soul_defense.total};
    event.stats.thunder = {character.stats.thunder.attack,
                           character.stats.thunder.defense};
    event.stats.fire = {character.stats.fire.attack,
                        character.stats.fire.defense};
    event.stats.ice = {character.stats.ice.attack, character.stats.ice.defense};
    event.stats.rotten = {character.stats.rotten.attack,
                          character.stats.rotten.defense};
    event.stats.weight = {23132, character.stats.weight.total};
    event.character_id = character.id;
    client.send(event);

    events::LoadFunctionBar function_bar;
    function_bar[0] = events::LoadFunctionBar::Function{3, 19};
    client.send(function_bar);
  }


  static void interact(IClient &client, const commands::Interact &command) {
    if (command.code == 1) {
      events::ShowEmote event;
      event.entity = 1;
      event.emote = command.entity;
      client.send(event);
    }
  }

  static void logout(IClient &client, const commands::Logout &command) {
    client.disconnect();
  }

  static void disconnect(IClient &client,
                         const IClient::ConnectionClosed &command,
                         Manager &manager) {
    manager.erase(&client);
  }
};

}// namespace openao::game::character

#endif// OPENAO_GAME_CHARACTER_CHARACTERCONTROLLER_H
