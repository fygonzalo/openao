
#ifndef OPENAO_MODEL_ATTRIBUTES_H
#define OPENAO_MODEL_ATTRIBUTES_H

#include <cstdint>
namespace Model {
struct Attributes {
  uint8_t gender;
  uint8_t hair_style;
  uint8_t height;
  uint8_t hair_color;
  uint8_t skin_color;
};
}// namespace Model

#endif// OPENAO_MODEL_ATTRIBUTES_H
