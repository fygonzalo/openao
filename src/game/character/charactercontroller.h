#ifndef OPENAO_GAME_CHARACTER_CHARACTERCONTROLLER_H
#define OPENAO_GAME_CHARACTER_CHARACTERCONTROLLER_H

#include "transport/iclient.h"

#include "character/commands/authenticatecommand.h"
#include "character/events/characterdetailevent.h"
#include "character/events/loadfunctionbarevent.h"

using namespace openao::framework::transport;
using namespace openao::game::character::commands;
using namespace openao::game::character::events;


namespace openao::game::character {

class CharacterController {
public:
  static void authenticate(IClient &client,
                           const AuthenticateCommand &command) {


    CharacterDetailEvent event;

    event.entityid = 1;
    event.position.x = 30;
    event.position.y = 30;
    event.name = "Bugs";
    event.title = "no-bugs";
    event.orientation = 0;
    event.shape = 0;
    event.attributes.gender = 1;
    event.attributes.hair_color = 0;
    event.attributes.hair_style = 0;
    event.attributes.height = 0;
    event.attributes.skin_color = 0;
    event.faction = 5;
    event.level = 1;
    event.experience = 0;
    event.rank = 1;
    event.credits = 0;
    event.stats.hp = {5, 20};
    event.stats.mp = {5, 20};
    event.stats.sp = {1000, 1000};
    event.stats.attack_base = 10;
    event.stats.attack_right = 10;
    event.stats.attack_left = 10;
    event.stats.defense = {10, 20};
    event.stats.spell_attack = {20, 30};
    event.stats.spell_defense = {30, 30};
    event.stats.rigor = {10, 20};
    event.stats.agility = {20, 30};
    event.stats.critical = {10, 20};
    event.stats.stamina = {10, 20};
    event.stats.soul_defense = {10, 20};
    event.stats.thunder = {10, 20};
    event.stats.fire = {10, 20};
    event.stats.ice = {10, 20};
    event.stats.rotten = {5, 9};
    event.stats.weight = {10, 20};
    event.character_id = 1;
    client.send(event);

    LoadFunctionBarEvent function_bar;
    function_bar[0] = LoadFunctionBarEvent::Function(3, 19);
    client.send(function_bar);
  }
};

}// namespace openao::game::character

#endif// OPENAO_GAME_CHARACTER_CHARACTERCONTROLLER_H
