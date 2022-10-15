
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_CHARACTER_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_CHARACTER_H

#include <pqxx/pqxx>

#include "datasources/icharacter.h"
#include "datasources/impl/pqxx/common/character.h"

namespace Datasources::PQXX {
class Character : public ICharacter {
public:
  Character(pqxx::connection &connection) : connection_(connection) {}

  Model::Characters get_characters_by_account(uint32_t account_id) override {
    pqxx::work w{connection_};


    auto results = w.exec("SELECT * FROM character WHERE account_id = " +
                          w.quote(account_id));

    w.commit();

    if (results.empty()) return {};
    if (results.size() > 3) throw "Too many characters";

    Model::Characters characters;

    for (int i = 0; i < results.size(); i++) {
      pqxx::row r = results[i];
      Model::Character &c = characters.characters[i];
      deserialize(r, c);
    };

    return characters;
  }

  Model::Character get_character_by_id(uint32_t id) override {
    pqxx::work w{connection_};

    auto r = w.exec1("SELECT * FROM character WHERE id = " + w.quote(id));

    Model::Character c{};
    deserialize(r, c);

    return c;
  }

  void update_character(Model::Character &character) override {
    pqxx::work w{connection_};


    auto r = w.exec("UPDATE character SET "
                    "title = " + w.quote(character.title.c_str()) + ","
                    "gender = " + w.quote((int)character.attributes.gender) + ","
                    "hair_style = " + w.quote((int)character.attributes.hair_style) + ","
                    "height = " + w.quote((int)character.attributes.height) + ","
                    "hair_color = " + w.quote((int)character.attributes.hair_color) + ","
                    "skin_color = " + w.quote((int)character.attributes.skin_color) + ","
                    "level = " + w.quote((int)character.level) + ","
                    "experience = " + w.quote((int)character.experience) + ","
                    "rank = " + w.quote((int)character.rank) + ","
                    "credits = " + w.quote((int)character.credits) + ","
                    "faction = " + w.quote((int)character.faction) + ","
                    "stage = " + w.quote((int)character.stage) + ","
                    "position_x = " + w.quote((int)character.position.x ) + ","
                    "position_y = " + w.quote((int)character.position.y ) + ","
                    "orientation = " + w.quote((int)character.position.orientation ) + ","
                    "head = " + w.quote((int)character.equipment.hand ) + ","
                    "body = " + w.quote((int)character.equipment.body ) + ","
                    "main_hand = " + w.quote((int)character.equipment.main_hand ) + ","
                    "off_hand = " + w.quote((int)character.equipment.off_hand) + ","
                    "hand = " + w.quote((int)character.equipment.hand ) + ","
                    "feet = " + w.quote((int)character.equipment.feet ) + ","
                    "back = " + w.quote((int)character.equipment.back ) + ","
                    "ride = " + w.quote((int)character.equipment.ride ) + ","
                    "shape = " + w.quote((int)character.shape ) +
                    "WHERE id = " + w.quote(character.id));

    w.commit();
  }

private:
  pqxx::connection &connection_;
};
}// namespace Datasources::PQXX

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_CHARACTER_H
