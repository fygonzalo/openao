#ifndef OPENAO_LOGIN_ACCOUNT_REPOSITORIES_IMPL_ACCOUNTREPOSITORY_H
#define OPENAO_LOGIN_ACCOUNT_REPOSITORIES_IMPL_ACCOUNTREPOSITORY_H

#include <base64.h>

#include <sqlpp11/postgresql/connection.h>
#include <sqlpp11/postgresql/exception.h>
#include <sqlpp11/sqlpp11.h>

#include "account/repositories/iaccountrepository.h"
#include "schema.h"

using namespace openao::login::account::repositories;
using namespace openao::database;

namespace openao::login::account::repositories::impl {


class AccountRepository : public IAccountRepository {
public:
  AccountRepository(sqlpp::postgresql::connection &conn) : conn_(conn){};


  std::optional<Account>
  get_by_username_and_password(std::string username,
                               std::string password) override {

    PUBLICAccount table;

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

}// namespace openao::login::account::repositories::impl

#endif// OPENAO_LOGIN_ACCOUNT_REPOSITORIES_IMPL_ACCOUNTREPOSITORY_H
