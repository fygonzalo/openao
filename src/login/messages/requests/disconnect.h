
#ifndef OPENAO_LOGIN_MESSAGES_REQUESTS_DISCONNECT_H
#define OPENAO_LOGIN_MESSAGES_REQUESTS_DISCONNECT_H

#include <cstdint>
namespace Login::Messages::Requests {

struct Disconnect {

  static const uint16_t type = 0xFFFF;

  void deserialize(BinaryBuffer &archive) {}

  void serialize(BinaryBuffer &archive) {}
};

}// namespace Login::Messages::Requests

#endif// OPENAO_LOGIN_MESSAGES_REQUESTS_DISCONNECT_H
