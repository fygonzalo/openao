
#ifndef OPENAO_LOGIN_MESSAGES_REQUESTS_CHANGE_PIN_H
#define OPENAO_LOGIN_MESSAGES_REQUESTS_CHANGE_PIN_H

#include "utils/string.h"

namespace Login::Messages::Requests {

struct ChangePin {
  static const uint16_t type = 9;

  String old_pin{32};
  String new_pin{32};

  template<typename Archive>
  void deserialize(Archive& archive) {
    archive.read(old_pin);
    archive.read(new_pin);

  }
};

}

#endif// OPENAO_LOGIN_MESSAGES_REQUESTS_CHANGE_PIN_H
