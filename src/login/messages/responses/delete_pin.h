
#ifndef OPENAO_LOGIN_MESSAGES_RESPONSES_DELETE_PIN_H
#define OPENAO_LOGIN_MESSAGES_RESPONSES_DELETE_PIN_H

#include "utils/string.h"

namespace Login::Messages::Responses {

struct DeletePin {
  static const uint16_t type = 8;

  bool status;

  void serialize(BinaryBuffer& archive) const {
    archive.write(status);
  }
};

}

#endif// OPENAO_LOGIN_MESSAGES_RESPONSES_DELETE_PIN_H
