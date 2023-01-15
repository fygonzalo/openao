
#include "serialization/attributes.h"

namespace Serialization {

void serialize(BinaryBuffer &archive, Model::Attributes &a) {
  archive.write(a.gender);
  archive.write(a.hair_style);
  archive.write(a.height);
  archive.write(a.hair_color);
  archive.write(a.skin_color);
}

void deserialize(BinaryBuffer &archive, Model::Attributes &a) {
  archive.read(a.gender);
  archive.read(a.hair_style);
  archive.read(a.height);
  archive.read(a.hair_color);
  archive.read(a.skin_color);
}

}// namespace Serialization