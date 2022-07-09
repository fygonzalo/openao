
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_CHARACTER_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_CHARACTER_H

#include <pqxx/pqxx>

#include "repositories/icharacter.h"
#include "repositories/impl/pqxx/common/character.h"

namespace Repositories::PQXX {
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

private:
  pqxx::connection &connection_;
};
}// namespace Repositories::PQXX

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_CHARACTER_H
