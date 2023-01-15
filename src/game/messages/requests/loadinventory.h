
#ifndef OPENAO_GAME_MESSAGES_REQUESTS_LOADINVENTORY_H
#define OPENAO_GAME_MESSAGES_REQUESTS_LOADINVENTORY_H

#include "utils/binarybuffer.h"
#include <cstdint>

namespace Game::Messages::Requests {

struct LoadInventory {
  static const uint16_t type = 3;

  void deserialize(BinaryBuffer &buffer) {

  }

};

}

#endif// OPENAO_GAME_MESSAGES_REQUESTS_LOADINVENTORY_H
