#ifndef OPENAO_LOGIN_ACCOUNT_REPOSITORY_ICHARACTERREPOSITORY_H
#define OPENAO_LOGIN_ACCOUNT_REPOSITORY_ICHARACTERREPOSITORY_H

#include <vector>

#include "account/repository/characterinfo.h"
#include "di/injectable.h"

namespace openao::login::account::repository {

class ICharacterRepository : public framework::di::Injectable {
public:
  virtual ~ICharacterRepository() = default;

  virtual std::vector<Character>
  get_characters_by_account_id(int account_id) = 0;
};

}// namespace openao::login::account::repository

#endif// OPENAO_LOGIN_ACCOUNT_REPOSITORY_ICHARACTERREPOSITORY_H
