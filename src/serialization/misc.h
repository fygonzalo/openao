
#ifndef OPENAO_SERIALIZATION_MISC_H
#define OPENAO_SERIALIZATION_MISC_H

#include "model/misc.h"

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

#endif// OPENAO_SERIALIZATION_MISC_H
