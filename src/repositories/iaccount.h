
#ifndef OPENAO_IACCOUNT_H
#define OPENAO_IACCOUNT_H

#include "model/account.h"
#include <optional>

namespace Repositories {
class IAccount {
public:
  virtual std::optional<Model::Account>
  find_account_by_username_password(std::string username,
                                    std::string password) = 0;
};
}// namespace Repositories
#endif// OPENAO_IACCOUNT_H
