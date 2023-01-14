
#ifndef OPENAO_LOGIN_MESSAGES_REQUESTS_SET_PIN_H
#define OPENAO_LOGIN_MESSAGES_REQUESTS_SET_PIN_H

#include "utils/string.h"

namespace Login::Messages::Requests {

struct SetPin {
  static const uint16_t type = 7;

  String password{32};
  String pin{32};

  template<typename Archive>
  void deserialize(Archive& archive) {
    archive.read(password);
    archive.read(pin);
  }
};

}

#endif// OPENAO_LOGIN_MESSAGES_REQUESTS_SET_PIN_H
