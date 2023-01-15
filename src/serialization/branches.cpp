
#include "serialization/branches.h"

namespace Serialization {

void serialize(BinaryBuffer &archive,  Model::Branches &bb) {
  archive.write((uint32_t) bb.statuses.size());
  archive.set(0, 51);
  for (auto &v: bb.statuses) { archive.write(v); }
}

}