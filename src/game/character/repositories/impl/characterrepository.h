#ifndef OPENAO_GAME_CHARACTER_REPOSITORIES_IMPL_CHARACTERREPOSITORY_H
#define OPENAO_GAME_CHARACTER_REPOSITORIES_IMPL_CHARACTERREPOSITORY_H

#include "schema.h"
#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>

#include "character/repositories/icharacterrepository.h"

using namespace openao::database;
using namespace openao::game::character::repositories;

namespace openao::game::character::repositories::impl {

class CharacterRepository : public ICharacterRepository {
public:
  CharacterRepository(sqlpp::postgresql::connection &conn) : conn_(conn) {}

  Character get(uint32_t id) override {
    PUBLICCharacter table;

    auto result = conn_(
            select(sqlpp::all_of(table)).from(table).where(table.id == id));

    if (result.empty()) { throw "Couldn't find character with id"; }

    Character character;
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

private:
  sqlpp::postgresql::connection &conn_;
};

}// namespace openao::game::character::repositories::impl

#endif// OPENAO_GAME_CHARACTER_REPOSITORIES_IMPL_CHARACTERREPOSITORY_H