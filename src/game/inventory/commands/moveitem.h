#ifndef OPENAO_GAME_INVENTORY_COMMANDS_MOVEITEM_H
#define OPENAO_GAME_INVENTORY_COMMANDS_MOVEITEM_H

#include "event.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;

namespace openao::game::inventory::commands {

struct MoveItem : framework::IEvent {

  uint16_t source;
  uint16_t destination;

  void deserialize(BinaryBuffer &buffer) {
    buffer.read(source);
    buffer.read(destination);
  }
};

}// namespace openao::game::inventory::commands

#endif// OPENAO_GAME_INVENTORY_COMMANDS_MOVEITEM_H
