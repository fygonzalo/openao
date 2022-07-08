
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_CHARACTER_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_CHARACTER_H

#include <pqxx/pqxx>

#include "repositories/icharacter.h"
#include "repositories/impl/pqxx/common/attributes.h"
#include "repositories/impl/pqxx/common/equipment.h"

namespace Repositories::PQXX {
class Character : public ICharacter {
public:
  Character(pqxx::connection &connection) : connection_(connection) {}

  Model::Characters get_characters_by_account(uint32_t account_id) override {
    pqxx::work w{connection_};


    auto results = w.exec(
            "SELECT id, account_id, index, name, title, gender,"
            "hair_style, height, hair_color, skin_color, "
            "birthday_month, birthday_day, blood, place, "
            "job, face, personality, level, experience, rank, "
            "credits, faction, stage, position_x, position_y, orientation, "
            "head, body, main_hand, off_hand, hand, feet, back, ride, shape, "
            "hp_current, hp_total, mp_current, mp_total, sp_current, sp_total, "
            "weight, attack_base, attack_right, attack_left, defense_base, "
            "defense_total, spell_defense_base, spell_defense_total, "
            "rigor_base, rigor_total, agility_base, agility_total, "
            "critical_base, critical_total, stamina_base, stamina_total, "
            "soul_defense_base, sould_defense_total, thunder_attack, "
            "thunder_defense, fire_attack, fire_defense, rotten_attack, "
            "rotten_defense FROM character WHERE account_id = " +
            w.quote(account_id));

    w.commit();

    if (results.empty()) return {};

    if (results.size() > 3) throw "Too many characters";

    Model::Characters characters;

    for (int i = 0; i < results.size(); i++) {
      pqxx::row r = results[i];

      Model::Character &c = characters.characters[i];
      c.index = r["index"].as<int>();
      c.level = r["level"].as<int>();
      c.faction = r["faction"].as<int>();
      deserialize(r, c.attributes);
      c.stage = r["stage"].as<int>();
      c.shape = r["shape"].as<int>();
      c.id = r["id"].as<int>();
      c.name = r["name"].as<std::string>();
      deserialize(r, c.equipment);
      c.stats.hp_current = r["hp_current"].as<int>();
      c.stats.mp_current = r["mp_current"].as<int>();
      c.title = r["title"].as<std::string>();

      characters.hps[i] = r["hp_total"].as<int>();
      characters.mps[i] = r["mp_total"].as<int>();
    };

    return characters;
  }

  Model::Character get_character_by_id(uint32_t id) override {
    pqxx::work w{connection_};

    auto r = w.exec1("SELECT * FROM character WHERE id = " + w.quote(id));

    Model::Character c{};
    c.index = r["index"].as<int>();
    c.level = r["level"].as<int>();
    c.faction = r["faction"].as<int>();
    deserialize(r, c.attributes);
    c.stage = r["stage"].as<int>();
    c.shape = r["shape"].as<int>();
    c.id = r["id"].as<int>();
    c.name = r["name"].as<std::string>();
    deserialize(r, c.equipment);
    c.stats.hp_current = r["hp_current"].as<int>();
    c.stats.mp_current = r["mp_current"].as<int>();
    c.title = r["title"].as<std::string>();
  }

private:
  pqxx::connection &connection_;
};
}// namespace Repositories::PQXX

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_CHARACTER_H
