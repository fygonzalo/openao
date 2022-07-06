
#ifndef OPENAO_AUTHREQUEST_H
#define OPENAO_AUTHREQUEST_H

#include <string>

#include "login/type.h"
#include "transport/binarybuffer.h"

struct AuthRequest {
  static const RequestType type = RequestType::AUTH;

  std::string username;
  std::string password;

  void deserialize(BinaryBuffer& buffer) {
    username.resize(21);
    buffer.read(username);

    password.resize(32);
    buffer.read(password);
  }
};

#endif// OPENAO_AUTHREQUEST_H
