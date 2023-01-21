#ifndef OPENAO_LOGIN_ACCOUNT_MODEL_INFO_H
#define OPENAO_LOGIN_ACCOUNT_MODEL_INFO_H

#include <string>

namespace openao::login::account::model {

struct Info {
  int id;
  std::string username;
  int slots;
  std::string pin;
};

}// namespace openao::login::account::model

#endif// OPENAO_LOGIN_ACCOUNT_MODEL_INFO_H
