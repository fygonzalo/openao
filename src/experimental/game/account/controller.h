
#ifndef OPENAO_EXPERIMENTAL_GAME_ACCOUNT_CONTROLLER_H
#define OPENAO_EXPERIMENTAL_GAME_ACCOUNT_CONTROLLER_H

#include "experimental/transport/client.h"

#include "experimental/game/account/authenticatecommand.h"
#include "experimental/game/account/logoutcommand.h"
#include "experimental/game/account/service.h"

#include "experimental/game/account/accountmanager.h"
#include "experimental/game/character/manager.h"
#include "experimental/game/character/service.h"
#include "experimental/game/stage.h"

using namespace openao::experimental::transport;

namespace openao::experimental::game::account {

class AccountController {
public:
  static void logout(Client &client, const LogoutCommand &command,
                     AccountManager &account_manager,
                     character::CharacterManager &character_manager,
                     Stage &stage) {
    stage.leave(client);
    character_manager.remove(client);
    account_manager.remove(client);
  }

  static void authenticate(Client &client, const AuthenticateCommand &command,
                           AccountManager &account_manager,
                           character::CharacterManager &character_manager,
                           character::CharacterService &character_service,
                           Stage &stage) {
    // Validate command


    // Process data
    uint32_t account_id = command.account;

    auto connected = account_manager.get(account_id);
    if (connected) return;

    account_manager.insert(client, account_id);

    auto character = character_service.get_by_character_id(command.character);
    character_manager.insert(client, character);

    stage.join(client);
  }

private:
};

}// namespace openao::experimental::game::account


#endif// OPENAO_EXPERIMENTAL_GAME_ACCOUNT_CONTROLLER_H
