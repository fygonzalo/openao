
#ifndef OPENAO_SERIALIZATION_ATTRIBUTES_H
#define OPENAO_SERIALIZATION_ATTRIBUTES_H

#include "model/character.h"
#include "utils/binarybuffer.h"

namespace Serialization {

void serialize(BinaryBuffer &archive, Model::Attributes &a);

void deserialize(BinaryBuffer &archive, Model::Attributes &a);
}// namespace Serialization

#endif// OPENAO_SERIALIZATION_ATTRIBUTES_H
