
#ifndef OPENAO_LOGIN_ACCOUNT_ACCOUNTCONTROLLER_H
#define OPENAO_LOGIN_ACCOUNT_ACCOUNTCONTROLLER_H

#include "account/accountservice.h"
#include "account/authenticatecommand.h"
#include "account/characterlistevent.h"
#include "branches/branchesservice.h"
#include "transport/iclient.h"

using namespace openao::framework::transport;
using namespace openao::login::branches;

namespace openao::login::account {


class AccountController {
public:
  static void authenticate(IClient &client,
                           const AuthenticationCommand &command,
                           AccountService &account_service,
                           BranchesService &branches_service) {
    CharacterListEvent character_list;
    for (auto &c: character_list.characters) {
      c.account_name = command.username;
      c.account_id = 1;
    }
    character_list.branches.statuses = branches_service.get_branch_statuses();
    client.send(character_list);
  }
};

}// namespace openao::login::account

#endif// OPENAO_LOGIN_ACCOUNT_ACCOUNTCONTROLLER_H
