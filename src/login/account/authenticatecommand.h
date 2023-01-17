
#ifndef OPENAO_LOGIN_ACCOUNT_AUTHENTICATECOMMAND_H
#define OPENAO_LOGIN_ACCOUNT_AUTHENTICATECOMMAND_H

#include "event.h"
#include "utils/binarybuffer.h"
#include "utils/string.h"

using openao::framework::IEvent;
using namespace openao::framework::utils;

namespace openao::login::account {

struct AuthenticationCommand : IEvent {

  String username{20};
  String password{32};

  void deserialize(BinaryBuffer &archive) {
    archive.read(username);
    archive.read(password);
  }
};

}// namespace openao::login::account

#endif// OPENAO_LOGIN_ACCOUNT_AUTHENTICATECOMMAND_H
