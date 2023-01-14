
#ifndef OPENAO_LOGIN_MESSAGES_REQUESTS_DELETE_PIN_H
#define OPENAO_LOGIN_MESSAGES_REQUESTS_DELETE_PIN_H

#include "utils/string.h"

namespace Login::Messages::Requests {

struct DeletePin {
  static const uint16_t type = 10;

  String pin{32};

  template<typename Archive>
  void deserialize(Archive& archive) {
    archive.read(pin);
  }
};

}

#endif// OPENAO_LOGIN_MESSAGES_REQUESTS_DELETE_PIN_H
