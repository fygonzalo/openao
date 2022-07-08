
#ifndef OPENAO_MESSAGES_RESPONSES_REDIRECT_H
#define OPENAO_MESSAGES_RESPONSES_REDIRECT_H

#include <cstdint>

#include "model/gameserver.h"
#include "utils/binarybuffer.h"

namespace Login::Messages::Responses {
struct Redirect {
  static const uint16_t type = 0x04;

  uint32_t session{};
  Model::GameServer server;

  template <typename Archive>
  void serialize(Archive &archive) {
    archive.set(0, 2);
    archive.write(session);
    archive.set(1, 1);
    archive.write(server.ip);
    archive.write(server.port);
    archive.set(0, 5);
  }
};

}// namespace Login::Messages::Responses

#endif// OPENAO_MESSAGES_RESPONSES_REDIRECT_H
