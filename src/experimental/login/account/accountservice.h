
#ifndef OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_IACCOUNTSERVICE_H
#define OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_IACCOUNTSERVICE_H

#include <cstdint>

namespace openao::experimental::login::account {

class AccountService {
public:
  uint32_t get_account_id() { return 50; }
};

}// namespace openao::experimental::login::account

#endif// OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_IACCOUNTSERVICE_H
