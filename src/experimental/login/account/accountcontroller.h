
#ifndef OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_ACCOUNTCONTROLLER_H
#define OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_ACCOUNTCONTROLLER_H

#include "experimental/login/account/accountservice.h"
#include "experimental/login/account/authenticatecommand.h"
#include "experimental/login/account/characterlistevent.h"
#include "experimental/login/branches/branchesservice.h"
#include "experimental/transport/iclient.h"

using namespace openao::experimental::transport;
using namespace openao::experimental::login::branches;

namespace openao::experimental::login::account {


class AccountController {
public:
  static void authenticate(IClient *client,
                           const AuthenticationCommand &command,
                           AccountService **&account_service,
                           BranchesService **&branches_service) {
    CharacterListEvent character_list;
    std::cout << "Test" << std::endl;
    BranchesService* pBranches_service =
            reinterpret_cast<BranchesService *>(&branches_service);
    character_list.branches.statuses = pBranches_service->get_branch_statuses();
    client->send(character_list);
  }
};

}// namespace openao::experimental::login::account

#endif// OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_ACCOUNTCONTROLLER_H
