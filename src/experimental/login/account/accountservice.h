
#ifndef OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_IACCOUNTSERVICE_H
#define OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_IACCOUNTSERVICE_H

#include <cstdint>

#include "experimental/di/injectable.h"

namespace openao::experimental::login::account {

class AccountService : public di::Injectable {
public:

  uint32_t get_account_id() {
    return 50;
  }

};

}

#endif// OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_IACCOUNTSERVICE_H
