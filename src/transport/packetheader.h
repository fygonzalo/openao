
#ifndef OPENAO_PACKETHEADER_H
#define OPENAO_PACKETHEADER_H

#include <cstdint>

#include "transport/binarybuffer.h"

class PacketHeader {
public:
  uint16_t size;
  int16_t sequence;
  uint8_t flags;
  uint8_t checksum;

  void serialize(BinaryBuffer &buffer) const {
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

#endif// OPENAO_PACKETHEADER_H
