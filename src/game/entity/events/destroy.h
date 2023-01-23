#ifndef OPENAO_GAME_ENTITY_DESTROY_H
#define OPENAO_GAME_ENTITY_DESTROY_H

#include "event.h"
#include "utils/binarybuffer.h"
#include <cstdint>

using namespace openao::framework::utils;

namespace openao::game::entity {

struct Destroy : framework::IEvent {
  uint32_t entity_id;
  uint8_t reason;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(entity_id);
    buffer.write(reason);
  }
};

}// namespace openao::game::entity

#endif// OPENAO_GAME_ENTITY_DESTROY_H
