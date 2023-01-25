#ifndef OPENAO_GAME_CHARACTER_REPOSITORY_H
#define OPENAO_GAME_CHARACTER_REPOSITORY_H

#include "schema.h"
#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>

#include "character/irepository.h"

using namespace openao::database;
using namespace openao::game::character;

namespace openao::game::character {

class Repository : public IRepository {
public:
  Repository(sqlpp::postgresql::connection &conn) : conn_(conn) {}

  model::Character get(uint32_t id) override {
    PUBLICCharacter table;

    auto result = conn_(
            select(sqlpp::all_of(table)).from(table).where(table.id == id));

    if (result.empty()) { throw "Couldn't find character with id"; }

    model::Character character;
    const auto &row = result.front();
    character.id = row.id;
    character.name = row.name;
    character.title = row.title;
    character.attributes.gender = row.gender;
    character.attributes.hair_color = row.hairColor;
    character.attributes.hair_style = row.hairStyle;
    character.attributes.height = row.height;
    character.attributes.skin_color = row.skinColor;
    character.position.x = row.positionX;
    character.position.y = row.positionY;
    character.position.orientation = row.orientation;
    character.shape = row.shape;
    character.faction = row.faction;
    character.equipment.head = row.head;
    character.equipment.body = row.body;
    character.equipment.right_hand = row.rightHand;
    character.equipment.left_hand = row.leftHand;
    character.equipment.hand = row.hand;
    character.equipment.feet = row.feet;
    character.equipment.back = row.back;
    character.equipment.ride = row.ride;
    character.level = row.level;
    character.experience = row.experience;
    character.rank = row.rank;
    character.credits = row.credits;
    character.stats.hp.current = row.hpCurrent;
    character.stats.hp.total = row.hpTotal;
    character.stats.mp.current = row.mpCurrent;
    character.stats.mp.total = row.mpTotal;
    character.stats.sp.base = row.spCurrent;
    character.stats.sp.total = row.spTotal;
    character.stats.attack_base = row.attackBase;
    character.stats.attack_left = row.attackLeft;
    character.stats.attack_right = row.attackRight;
    character.stats.defense.current = row.defenseBase;
    character.stats.defense.total = row.defenseTotal;
    character.stats.spell_attack = {0, 0};
    character.stats.spell_defense.current = row.spellDefenseBase;
    character.stats.spell_defense.total = row.spellDefenseTotal;
    character.stats.rigor.base = row.rigorBase;
    character.stats.rigor.total = row.rigorTotal;
    character.stats.agility.base = row.agilityBase;
    character.stats.agility.total = row.agilityTotal;
    character.stats.critical.base = row.criticalBase;
    character.stats.critical.total = row.criticalTotal;
    character.stats.stamina.base = row.staminaBase;
    character.stats.stamina.total = row.staminaTotal;
    character.stats.soul_defense.base = row.soulDefenseBase;
    character.stats.soul_defense.total = row.soulDefenseTotal;
    character.stats.thunder.attack = row.thunderAttackTotal;
    character.stats.thunder.defense = row.thunderDefenseTotal;
    character.stats.fire.attack = row.fireAttackTotal;
    character.stats.fire.defense = row.fireDefenseTotal;
    character.stats.ice.attack = row.iceAttackTotal;
    character.stats.ice.defense = row.iceDefenseTotal;
    character.stats.rotten.attack = row.rottenAttackTotal;
    character.stats.rotten.defense = row.rottenDefenseTotal;
    character.stats.weight.total = row.weight;
    return character;
  }

  void save(model::Character &character) {
    PUBLICCharacter table;

    conn_(update(table)
                  .set(table.title = character.title,
                       table.positionX = character.position.x,
                       table.positionY = character.position.y,
                       table.orientation = character.position.orientation,
                       table.head = character.equipment.head,
                       table.body = character.equipment.body,
                       table.rightHand = character.equipment.right_hand,
                       table.leftHand = character.equipment.left_hand,
                       table.hand = character.equipment.hand,
                       table.feet = character.equipment.feet,
                       table.back = character.equipment.back,
                       table.ride = character.equipment.ride)
                  .where(table.id == character.id));
  }

private:
  sqlpp::postgresql::connection &conn_;
};

}// namespace openao::game::character

#endif// OPENAO_GAME_CHARACTER_REPOSITORY_H