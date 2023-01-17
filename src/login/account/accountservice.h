
#ifndef OPENAO_LOGIN_ACCOUNT_IACCOUNTSERVICE_H
#define OPENAO_LOGIN_ACCOUNT_IACCOUNTSERVICE_H

#include <cstdint>

namespace openao::login::account {

class AccountService {
public:
  uint32_t get_account_id() { return 50; }
};

}// namespace openao::login::account

#endif// OPENAO_LOGIN_ACCOUNT_IACCOUNTSERVICE_H
