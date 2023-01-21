#ifndef OPENAO_LOGIN_ACCOUNT_IREPOSITORY_H
#define OPENAO_LOGIN_ACCOUNT_IREPOSITORY_H

#include <optional>

#include "di/injectable.h"

#include "account/model/info.h"

namespace openao::login::account {

class IRepository : public framework::di::Injectable {
public:
  virtual std::optional<model::Info> get(std::string username,
                                         std::string password) = 0;
};

}// namespace openao::login::account

#endif// OPENAO_LOGIN_ACCOUNT_IREPOSITORY_H
