
#ifndef OPENAO_FRAMEWORK_TRANSPORT_PACKETHEADER_H
#define OPENAO_FRAMEWORK_TRANSPORT_PACKETHEADER_H

#include <cstdint>

#include "utils/binarybuffer.h"

using openao::framework::utils::BinaryBuffer;

namespace openao::framework::transport {

class PacketHeader {
public:
  uint16_t size;
  int16_t sequence;
  uint8_t flags;
  uint8_t checksum;

  void serialize(BinaryBuffer &buffer) {
    buffer.write((uint16_t) (size ^ 0x1357));
    buffer.write((uint16_t) (sequence ^ size));
    buffer.write((uint8_t) (flags ^ size));
    buffer.write(checksum);
  }

  void deserialize(BinaryBuffer &buffer) {
    buffer.read(size);
    buffer.read(sequence);
    buffer.read(flags);
    buffer.read(checksum);

    size ^= 0x1357;
    sequence ^= size;
    flags ^= size;
  }
};

}// namespace openao::framework::transport

#endif// OPENAO_FRAMEWORK_TRANSPORT_PACKETHEADER_H
