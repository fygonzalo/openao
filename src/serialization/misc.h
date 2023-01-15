
#ifndef OPENAO_SERIALIZATION_MISC_H
#define OPENAO_SERIALIZATION_MISC_H

#include "model/misc.h"
#include "utils/binarybuffer.h"

namespace Serialization {

void deserialize(BinaryBuffer &archive, Model::Misc &m);

}

#endif// OPENAO_SERIALIZATION_MISC_H
