
#ifndef OPENAO_LOGIN_MESSAGES_REQUESTS_DELETE_PIN_H
#define OPENAO_LOGIN_MESSAGES_REQUESTS_DELETE_PIN_H

#include "utils/string.h"

namespace Login::Messages::Requests {

struct DeletePin {
  static const uint16_t type = 10;

  String pin{32};

  void deserialize(BinaryBuffer &archive) { archive.read(pin); }
};

}// namespace Login::Messages::Requests

#endif// OPENAO_LOGIN_MESSAGES_REQUESTS_DELETE_PIN_H
