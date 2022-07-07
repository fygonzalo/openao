
#ifndef OPENAO_SERIALIZATION_BINARY_BRANCHES_H
#define OPENAO_SERIALIZATION_BINARY_BRANCHES_H

#include "model/branches.h"
#include "utils/binarybuffer.h"

namespace Serialization::Binary {
void serialize(BinaryBuffer &buffer, Model::Branches &bb) {
  buffer.write((uint32_t) bb.statuses.size());
  buffer.set(0, 51);
  for (auto &v: bb.statuses) { buffer.write(v); }
}
}// namespace Serialization::Binary

#endif// OPENAO_SERIALIZATION_BINARY_BRANCHES_H
