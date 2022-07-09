
#ifndef OPENAO_POSITION_H
#define OPENAO_POSITION_H

#include <cstdint>
namespace Model {

struct Position {
  uint32_t x;
  uint32_t y;
  uint32_t orientation;
};
}

#endif// OPENAO_POSITION_H
