
#ifndef OPENAO_LOGIN_MESSAGES_RESPONSES_SET_PIN_H
#define OPENAO_LOGIN_MESSAGES_RESPONSES_SET_PIN_H

#include "utils/string.h"

namespace Login::Messages::Responses {

struct SetPin {
  static const uint16_t type = 5;

  bool status;

  void serialize(BinaryBuffer& archive) {
    archive.write(status);
  }
};

}

#endif// OPENAO_LOGIN_MESSAGES_RESPONSES_SET_PIN_H
