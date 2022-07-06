
#ifndef OPENAO_MESSAGES_REQUESTS_AUTH_H
#define OPENAO_MESSAGES_REQUESTS_AUTH_H

#include "transport/string.h"
#include <string>

namespace Messages::Requests {

struct Auth {
  static const uint16_t type = 0x02;

  String username{20};
  String password{32};

  void deserialize(BinaryBuffer &buffer) {
    buffer.read(username);
    buffer.read(password);
  }
};
}// namespace Messages::Requests

#endif// OPENAO_MESSAGES_REQUESTS_AUTH_H
