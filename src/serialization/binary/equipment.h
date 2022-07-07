
#ifndef OPENAO_SERIALIZATION_BINARY_EQUIPMENT_H
#define OPENAO_SERIALIZATION_BINARY_EQUIPMENT_H

#include "model/character.h"
#include "utils/binarybuffer.h"

namespace Serialization::Binary {
void serialize(BinaryBuffer &buffer, Model::Equipment &e) {
  buffer.write(e.head);
  buffer.write(e.body);
  buffer.write(e.main_hand);
  buffer.write(e.off_hand);
  buffer.write(e.hand);
  buffer.write(e.feet);
  buffer.write(e.back);
  buffer.write(e.ride);
}
}// namespace Serialization::Binary

#endif// OPENAO_SERIALIZATION_BINARY_EQUIPMENT_H
