#ifndef OPENAO_LOGIN_ACCOUNT_REPOSITORIES_ACCOUNTINFO_H
#define OPENAO_LOGIN_ACCOUNT_REPOSITORIES_ACCOUNTINFO_H

#include <string>

namespace openao::login::account::repositories {

struct Account {
  int id;
  std::string username;
  int slots;
  std::string pin;
};

}// namespace openao::login::account::repositories

#endif// OPENAO_LOGIN_ACCOUNT_REPOSITORIES_ACCOUNTINFO_H
