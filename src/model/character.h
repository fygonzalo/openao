
#ifndef OPENAO_CHARACTER_H
#define OPENAO_CHARACTER_H

#include "attributes.h"
#include "equipment.h"
#include "stats.h"
#include "utils/binarybuffer.h"
#include "utils/string.h"

#include <cstdint>

namespace Model {

struct Character {
  uint8_t index = 0;
  uint32_t level = 0;
  uint8_t faction = 0;
  Attributes attributes;
  uint32_t stage = 0;
  uint32_t shape = 0;
  // Must be bigger than 0 otherwise the client will fail to render the
  // character
  uint32_t id = 0;
  String name{16, ""};
  Equipment equipment;
  Stats stats;
  String title{12, ""};
};
}// namespace Model

#endif// OPENAO_CHARACTER_H
