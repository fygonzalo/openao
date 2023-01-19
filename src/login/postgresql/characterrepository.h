#ifndef OPENAO_LOGIN_POSTGRESQL_CHARACTERREPOSITORY_H
#define OPENAO_LOGIN_POSTGRESQL_CHARACTERREPOSITORY_H


#include "account/repository/icharacterrepository.h"
#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>

#include "schema.h"

using namespace openao::login::account::repository;
using namespace openao::database;

namespace openao::login::postgresql {

class CharacterRepository : public ICharacterRepository {
public:
  CharacterRepository(sqlpp::postgresql::connection &conn) : conn_(conn){};

  std::vector<Character> get_characters_by_account_id(int account_id) override {

    PUBLICCharacter table;
    auto result = conn_(select(sqlpp::all_of(table))
                                .from(table)
                                .where(table.accountId == account_id));
    if (result.empty()) return {};

    std::vector<Character> character_list;
    for (auto &row: result) {
      Character &character = character_list.emplace_back();
      character.id = row.id;
      character.account_id = row.accountId;
      character.name = row.name;
      character.title = row.title;
      character.level = row.level;
      character.stage = row.stage;
      character.shape = row.shape;
      character.faction = row.faction;

      character.equipment.head = row.head;
      character.equipment.body = row.body;
      character.equipment.right_hand = row.mainHand;
      character.equipment.left_hand = row.offHand;
      character.equipment.hand = row.hand;
      character.equipment.feet = row.feet;
      character.equipment.back = row.back;
      character.equipment.ride = row.ride;
    }
    return character_list;
  }

private:
  sqlpp::postgresql::connection &conn_;
};

}// namespace openao::login::postgresql

#endif// OPENAO_LOGIN_POSTGRESQL_CHARACTERREPOSITORY_H
