#ifndef OPENAO_GAME_CHAT_SAYS_H
#define OPENAO_GAME_CHAT_SAYS_H

#include <cstdint>

#include "event.h"
#include "utils/binarybuffer.h"
#include "utils/string.h"

using namespace openao::framework::utils;

namespace openao::game::chat {

struct Says : framework::IEvent {

  uint32_t entity;
  String name{16};
  String message{80};

  void serialize(BinaryBuffer &buffer) {
    buffer.write(entity);
    buffer.write(name);
    buffer.write(message);
  }
};

}// namespace openao::game::chat

#endif// OPENAO_GAME_CHAT_SAYS_H
