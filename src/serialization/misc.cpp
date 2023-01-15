
#include "serialization/misc.h"

namespace Serialization {

void deserialize(BinaryBuffer &archive, Model::Misc &m) {
  archive.read(m.month);
  archive.read(m.day);
  archive.read(m.blood);
  archive.read(m.place);
  archive.read(m.job);
  archive.read(m.face);
  archive.read(m.personality);
}

}