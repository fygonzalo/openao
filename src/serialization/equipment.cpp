
#include "serialization/equipment.h"

namespace Serialization {

void serialize(BinaryBuffer &archive, Model::Equipment &e) {
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