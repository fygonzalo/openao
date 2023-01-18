#ifndef OPENAO_LOGIN_ACCOUNT_REPOSITORY_IACCOUNTREPOSITORY_H
#define OPENAO_LOGIN_ACCOUNT_REPOSITORY_IACCOUNTREPOSITORY_H

#include <optional>

#include "di/injectable.h"

#include "account/repository/accountinfo.h"

namespace openao::login::account::repository {

class IAccountRepository : public framework::di::Injectable {
public:
  virtual std::optional<Account>
  get_by_username_and_password(std::string username, std::string password) = 0;
};

}// namespace openao::login::account::repository

#endif// OPENAO_LOGIN_ACCOUNT_REPOSITORY_IACCOUNTREPOSITORY_H
