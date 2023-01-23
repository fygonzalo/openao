#ifndef OPENAO_GAME_CHARACTER_COMMANDS_LOGOUT_H
#define OPENAO_GAME_CHARACTER_COMMANDS_LOGOUT_H

#include "event.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;

namespace openao::game::character::commands {

struct Logout : framework::IEvent {

  void deserialize(BinaryBuffer &buffer) {}
};

}// namespace openao::game::character::commands

#endif// OPENAO_GAME_CHARACTER_COMMANDS_LOGOUT_H