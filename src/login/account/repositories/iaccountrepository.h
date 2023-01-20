#ifndef OPENAO_LOGIN_ACCOUNT_REPOSITORIES_IACCOUNTREPOSITORY_H
#define OPENAO_LOGIN_ACCOUNT_REPOSITORIES_IACCOUNTREPOSITORY_H

#include <optional>

#include "di/injectable.h"

#include "account/repositories/accountinfo.h"

namespace openao::login::account::repositories {

class IAccountRepository : public framework::di::Injectable {
public:
  virtual std::optional<Account>
  get_by_username_and_password(std::string username, std::string password) = 0;
};

}// namespace openao::login::account::repositories

#endif// OPENAO_LOGIN_ACCOUNT_REPOSITORIES_IACCOUNTREPOSITORY_H
