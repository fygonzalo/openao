
#ifndef OPENAO_MESSAGES_RESPONSES_REDIRECT_H
#define OPENAO_MESSAGES_RESPONSES_REDIRECT_H

#include <cstdint>

#include "model/gameserver.h"
#include "transport/binarybuffer.h"

namespace Login::Messages::Responses {
struct Redirect {
  static const uint16_t type = 0x04;

  uint32_t session{};
  Model::GameServer server;

  void serialize(BinaryBuffer &buffer) {
    buffer.set(0, 2);
    buffer.write(session);
    buffer.set(0, 1);
    buffer.write(server.ip);
    buffer.write(server.port);
    buffer.set(0, 5);
  }
};

}// namespace Login::Messages::Responses

#endif// OPENAO_MESSAGES_RESPONSES_REDIRECT_H