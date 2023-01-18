#ifndef OPENAO_LOGIN_ACCOUNT_REPOSITORY_ACCOUNTINFO_H
#define OPENAO_LOGIN_ACCOUNT_REPOSITORY_ACCOUNTINFO_H

#include <string>

namespace openao::login::account::repository {

struct Account {
  int id;
  std::string username;
  int slots;
  std::string pin;
};

}// namespace openao::login::account::repository

#endif// OPENAO_LOGIN_ACCOUNT_REPOSITORY_ACCOUNTINFO_H
