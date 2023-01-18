#ifndef OPENAO_LOGIN_POSTGRESQL_ACCOUNTREPOSITORY_H
#define OPENAO_LOGIN_POSTGRESQL_ACCOUNTREPOSITORY_H

#include <base64.h>

#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>

#include "account/repository/iaccountrepository.h"
#include "postgresql/postgres.h"

using namespace openao::login::account::repository;

namespace openao::login::postgresql {


class AccountRepository : public IAccountRepository {
public:
  AccountRepository(sqlpp::postgresql::connection &conn) : conn_(conn){};


  std::optional<Account>
  get_by_username_and_password(std::string username,
                               std::string password) override {

    PublicAccount table;

    auto result =
            conn_(select(table.id, table.username, table.password, table.slots,
                         table.pin)
                          .from(table)
                          .where(table.username == username and
                                 table.password == base64_encode(password)));
    if (result.empty()) return {};

    const auto &row = result.front();


    Account account;
    account.id = row.id;
    account.username = row.username;
    account.slots = row.slots;
    account.pin = row.pin;
    return account;
  }

private:
  sqlpp::postgresql::connection &conn_;
};

}// namespace openao::login::postgresql

#endif// OPENAO_LOGIN_POSTGRESQL_ACCOUNTREPOSITORY_H
