
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_ACCOUNT_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_ACCOUNT_H

#include <base64.h>
#include <pqxx/pqxx>

#include "datasources/iaccount.h"

namespace Datasources::PQXX {
class Account : public IAccount {
public:
  Account(pqxx::connection &connection) : connection_(connection){};

  std::optional<Model::Account>
  find_account_by_username_password(std::string username,
                                    std::string password) override {
    pqxx::work w{connection_};

    pqxx::result results =
            w.exec("SELECT id, username, slots, (pin IS NOT NULL) AS pin FROM "
                   "account WHERE "
                   "username = " +
                   w.quote(username) +
                   "AND password = " + w.quote(base64_encode(password)));
    w.commit();

    if (results.size() > 1) throw "More than one user";

    if (results.empty()) return {};

    auto r = results[0];
    Model::Account account;
    account.id = r["id"].as<uint32_t>();
    account.username = r["username"].as<std::string>();
    account.slots = r["slots"].as<uint32_t>();
    account.pin = r["pin"].as<bool>();

    return account;
  }

  bool set_pin(int id, std::string password, std::string pin) override {
    pqxx::work w{connection_};

    auto r = w.exec("UPDATE account SET "
                    "pin = " +
                    w.quote(base64_encode(pin)) +
                    "WHERE id = " + w.quote(id) +
                    "AND password = " + w.quote(base64_encode(password)) +
                    "AND pin IS NULL");

    w.commit();
    return r.affected_rows() == 1;
  }

private:
  pqxx::connection &connection_;
};
}// namespace Datasources::PQXX

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_ACCOUNT_H
