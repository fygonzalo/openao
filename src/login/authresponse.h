
#ifndef OPENAO_AUTHRESPONSE_H
#define OPENAO_AUTHRESPONSE_H

#include <cstdint>

#include "login/type.h"

#include "model/characters.h"
#include "model/branches.h"

#include "transport/binarybuffer.h"
#include "transport/string.h"

enum class AuthStatus : uint16_t {
  OK = 0x00,
  RANDOM = 0xb2,
  ALREADY_LOGGED_IN = 0x97,
  INVALID_USERNAME_PASSWORD = 0x98
};

struct InvalidAuthResponse {

  static const ResponseType type = ResponseType::AUTH;

  AuthStatus code = AuthStatus::OK;
  std::string args;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(static_cast<uint16_t>(code));
    buffer.write((uint8_t) 2);
    buffer.write(args);
    buffer.write(args);
  }
};

struct ValidAuthResponse {

  static const ResponseType type = ResponseType::AUTH;

  AuthStatus code = AuthStatus::OK;
  Model::Characters characters;
  Model::Branches branches;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(static_cast<uint16_t>(code));
    buffer.write((uint8_t)0);
    buffer.write(characters);
    buffer.write(branches);
  }
};

#endif// OPENAO_AUTHRESPONSE_H
