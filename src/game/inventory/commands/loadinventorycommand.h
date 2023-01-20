#ifndef OPENAO_GAME_INVENTORY_COMMANDS_LOADINVENTORYCOMMAND_H
#define OPENAO_GAME_INVENTORY_COMMANDS_LOADINVENTORYCOMMAND_H

#include "event.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;

namespace openao::game::inventory::commands {

struct LoadInventoryCommand : framework::IEvent {
  void deserialize(BinaryBuffer &buffer){};
};

}// namespace openao::game::inventory::commands


#endif// OPENAO_GAME_INVENTORY_COMMANDS_LOADINVENTORYCOMMAND_H