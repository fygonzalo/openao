
#ifndef OPENAO_DATASOURCES_IACCOUNT_H
#define OPENAO_DATASOURCES_IACCOUNT_H

#include "model/account.h"
#include <optional>

namespace Datasources {
class IAccount {
public:
  virtual ~IAccount() {}

  virtual std::optional<Model::Account>
  find_account_by_username_password(std::string username,
                                    std::string password) = 0;

  virtual bool set_pin(int id, std::string password, std::string pin) = 0;
};
}// namespace Datasources
#endif// OPENAO_DATASOURCES_IACCOUNT_H
