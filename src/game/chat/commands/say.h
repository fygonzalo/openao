#ifndef OPENAO_GAME_CHAT_SAY_H
#define OPENAO_GAME_CHAT_SAY_H

#include "event.h"
#include "utils/binarybuffer.h"
#include "utils/string.h"

using namespace openao::framework::utils;

namespace openao::game::chat {

struct Say : framework::IEvent {

  String message{80};

  void deserialize(BinaryBuffer &buffer) { buffer.read(message); }
};

}// namespace openao::game::chat

#endif// OPENAO_GAME_CHAT_SAY_H
