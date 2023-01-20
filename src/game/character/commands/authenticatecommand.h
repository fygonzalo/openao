#ifndef OPENAO_GAME_CHARACTER_COMMANDS_AUTHENTICATECOMMAND_H
#define OPENAO_GAME_CHARACTER_COMMANDS_AUTHENTICATECOMMAND_H

#include <cstdint>

#include "event.h"

#include "utils/binarybuffer.h"
#include "utils/string.h"

using namespace openao::framework::utils;

namespace openao::game::character::commands {

struct AuthenticateCommand : framework::IEvent {

  String version{16};
  uint32_t account_id;
  uint32_t character_id;
  uint32_t stage;
  uint32_t session_id;

  void deserialize(BinaryBuffer &buffer) {
    buffer.read(version);
    buffer.read(account_id);
    buffer.read(character_id);
    buffer.read(stage);
    buffer.read(session_id);
  }
};

}// namespace openao::game::character::commands

#endif// OPENAO_GAME_CHARACTER_COMMANDS_AUTHENTICATECOMMAND_H
