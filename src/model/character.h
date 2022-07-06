
#ifndef OPENAO_CHARACTER_H
#define OPENAO_CHARACTER_H

#include "transport/binarybuffer.h"
#include "transport/string.h"

#include <cstdint>

namespace Model {
  struct Attributes {
    uint8_t gender;
    uint8_t hair_style;
    uint8_t height;
    uint8_t hair_color;
    uint8_t skin_color;
  };

  struct Equipment {
    uint32_t head;
    uint32_t body;
    uint32_t main_hand;
    uint32_t off_hand;
    uint32_t hand;
    uint32_t feet;
    uint32_t back;
    uint32_t ride;
  };

  struct Stats {
    uint32_t hp_current;
    uint32_t mp_current;
  };

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
