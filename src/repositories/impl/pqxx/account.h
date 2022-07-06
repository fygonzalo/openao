
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_ACCOUNT_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_ACCOUNT_H

#include <pqxx/pqxx>

#include "repositories/iaccount.h"

namespace Repositories::PQXX {
  class Account : public IAccount {
  public:
    Account(pqxx::connection &connection) : connection_(connection){};

    std::optional<Model::Account>
    find_account_by_username_password(std::string username,
                                      std::string password) override {
      pqxx::work w{connection_};

      pqxx::result results = w.exec(
              "SELECT id, username, slots FROM account WHERE username = " +
              w.quote(username));
      w.commit();

      if (results.size() > 1)
        throw "More than one user";

      if (results.empty())
        return {};

      auto r = results[0];
      Model::Account account;
      account.id = r["id"].as<uint32_t>();
      account.username = r["username"].as<std::string>();
      account.slots = r["slots"].as<uint32_t>();

      return account;
    }

  private:
    pqxx::connection &connection_;
  };
}// namespace Repositories::PQXX

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_ACCOUNT_H
