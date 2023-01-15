
#ifndef OPENAO_CHARACTER_H
#define OPENAO_CHARACTER_H

#include "model/attributes.h"
#include "model/equipment.h"
#include "model/generic.h"
#include "model/misc.h"
#include "model/position.h"
#include "model/stats.h"

#include "utils/binarybuffer.h"
#include "utils/string.h"

#include "utils/flagset.h"
#include <cstdint>

namespace Model {

struct Character {
  enum class Properties : uint8_t {
    UNK_1,
    PLV,
    UNK_2,
    DEAD,
    NEW,
    UNK_3,
    DELETE_TIMER_ENABLE,
    DELETE_TIMER_FINISH,
    _
  };


  // Must be bigger than 0 otherwise the client will fail to render the
  // character
  uint32_t id = 0;
  uint32_t account_id;
  uint8_t index = 0;

  String name{16};
  String title{12};

  Attributes attributes;
  Misc misc;

  uint32_t level = 0;
  uint64_t experience;

  uint8_t rank = 0;
  uint32_t credits = 0;

  uint8_t faction = 0;

  uint32_t stage = 0;
  Position position;

  Equipment equipment;

  FlagSet<Properties> properties;

  uint32_t shape;
  uint32_t deletion_timer = 0;

  Stats stats;
  Skills skills;
};
}// namespace Model

#endif// OPENAO_CHARACTER_H
