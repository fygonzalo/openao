
#ifndef OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_AUTHENTICATECOMMAND_H
#define OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_AUTHENTICATECOMMAND_H

#include "experimental/reactor/event.h"
#include "utils/binarybuffer.h"
#include "utils/string.h"

using namespace openao::experimental::reactor;

namespace openao::experimental::login::account {

struct AuthenticationCommand : Event<AuthenticationCommand> {

  String username{20};
  String password{32};

  void deserialize(BinaryBuffer& archive) {
    archive.read(username);
    archive.read(password);
  }

};

}

#endif// OPENAO_EXPERIMENTAL_LOGIN_ACCOUNT_AUTHENTICATECOMMAND_H
