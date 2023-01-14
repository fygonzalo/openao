
#ifndef OPENAO_SERIALIZATION_BRANCHES_H
#define OPENAO_SERIALIZATION_BRANCHES_H

#include "model/branches.h"
#include "utils/binarybuffer.h"

namespace Serialization {

void serialize(BinaryBuffer &archive,  Model::Branches &bb) {
  archive.write((uint32_t) bb.statuses.size());
  archive.set(0, 51);
  for (auto &v: bb.statuses) { archive.write(v); }
}
}// namespace Serialization

#endif// OPENAO_SERIALIZATION_BRANCHES_H
