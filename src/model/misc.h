
#ifndef OPENAO_MODEL_MISC_H
#define OPENAO_MODEL_MISC_H
#include <cstdint>
namespace Model {
struct Misc {
  uint8_t month;
  uint8_t day;
  uint8_t blood;
  uint8_t place;
  uint8_t job;
  uint8_t face;
  uint8_t personality;
};
}// namespace Model
#endif// OPENAO_MODEL_MISC_H
