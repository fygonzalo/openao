
#ifndef OPENAO_SERIALIZATION_BINARY_ATTRIBUTES_H
#define OPENAO_SERIALIZATION_BINARY_ATTRIBUTES_H

#include "model/character.h"
#include "utils/binarybuffer.h"

namespace Serialization::Binary {
void serialize(BinaryBuffer &buffer, Model::Attributes &a) {
  buffer.write(a.gender);
  buffer.write(a.hair_style);
  buffer.write(a.height);
  buffer.write(a.hair_color);
  buffer.write(a.skin_color);
}
}// namespace Serialization::Binary

#endif// OPENAO_SERIALIZATION_BINARY_ATTRIBUTES_H
