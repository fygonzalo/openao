
#ifndef OPENAO_MESSAGES_REQUESTS_AUTH_H
#define OPENAO_MESSAGES_REQUESTS_AUTH_H

#include "login/type.h"
#include "transport/string.h"
#include <string>

namespace Messages::Requests {

  struct Auth {
    static const RequestType type = RequestType::AUTH;

    String username{20};
    String password{32};

    void deserialize(BinaryBuffer& buffer) {
      buffer.read(username);
      buffer.read(password);
    }
  };
}

#endif// OPENAO_MESSAGES_REQUESTS_AUTH_H
