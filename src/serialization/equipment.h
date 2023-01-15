
#ifndef OPENAO_SERIALIZATION_EQUIPMENT_H
#define OPENAO_SERIALIZATION_EQUIPMENT_H

#include "model/character.h"
#include "utils/binarybuffer.h"

namespace Serialization {

void serialize(BinaryBuffer &archive, Model::Equipment &e);

}// namespace Serialization

#endif// OPENAO_SERIALIZATION_EQUIPMENT_H
