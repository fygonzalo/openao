
#ifndef OPENAO_SERIALIZATION_EQUIPMENT_H
#define OPENAO_SERIALIZATION_EQUIPMENT_H

#include "model/character.h"
#include "utils/binarybuffer.h"

namespace Serialization {
template <typename Archive>
void serialize(Archive &archive, Model::Equipment &e) {
  archive.write(e.head);
  archive.write(e.body);
  archive.write(e.main_hand);
  archive.write(e.off_hand);
  archive.write(e.hand);
  archive.write(e.feet);
  archive.write(e.back);
  archive.write(e.ride);
}
}// namespace Serialization

#endif// OPENAO_SERIALIZATION_EQUIPMENT_H
