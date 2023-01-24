#ifndef OPENAO_GAME_CHARACTER_COMMANDS_SET_TITLE_H
#define OPENAO_GAME_CHARACTER_COMMANDS_SET_TITLE_H

#include "event.h"
#include "utils/binarybuffer.h"
#include "utils/string.h"

using namespace openao::framework::utils;

namespace openao::game::character::commands {

struct SetTitle : framework::IEvent {

  String title{16};

  void deserialize(BinaryBuffer &buffer) { buffer.read(title); }
};

}// namespace openao::game::character::commands

#endif// OPENAO_GAME_CHARACTER_COMMANDS_SET_TITLE_H
