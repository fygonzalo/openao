
#ifndef OPENAO_EXPERIMENTAL_GAME_ACCOUNT_AUTHENTICATECOMMAND_H
#define OPENAO_EXPERIMENTAL_GAME_ACCOUNT_AUTHENTICATECOMMAND_H

#include <string>

namespace openao::experimental::game::account {

struct AuthenticateCommand {
  uint32_t account;
  uint32_t character;
  uint32_t stage;
  uint32_t session;
};

}// namespace openao::experimental::game::account

#endif// OPENAO_EXPERIMENTAL_GAME_ACCOUNT_AUTHENTICATECOMMAND_H
