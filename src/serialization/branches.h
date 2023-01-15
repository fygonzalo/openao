
#ifndef OPENAO_SERIALIZATION_BRANCHES_H
#define OPENAO_SERIALIZATION_BRANCHES_H

#include "model/branches.h"
#include "utils/binarybuffer.h"

namespace Serialization {

void serialize(BinaryBuffer &archive,  Model::Branches &bb);

}// namespace Serialization

#endif// OPENAO_SERIALIZATION_BRANCHES_H
