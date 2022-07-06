
#ifndef OPENAO_MODEL_EQUIPMENT_H
#define OPENAO_MODEL_EQUIPMENT_H

#include <cstdint>
namespace Model {
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
}// namespace Model

#endif// OPENAO_MODEL_EQUIPMENT_H
