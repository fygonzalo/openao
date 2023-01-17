
#ifndef OPENAO_FRAMEWORK_UTILS_BITSET_H
#define OPENAO_FRAMEWORK_UTILS_BITSET_H

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "utils/binarybuffer.h"

namespace openao::framework::utils {

template<size_t N>
class Bitset {
public:
  class Bit {
  public:
    bool flip() {
      byte_ ^= 1 << index_;
      return byte_ & (1 << index_);
    }

    bool operator==(Bit &&b2) const {
      return (byte_ & index_) == (b2.byte_ & b2.index_);
    }

    bool operator==(const bool b2) const {
      return (byte_ & (1 << index_)) == b2;
    }

  private:
    friend class Bitset;
    Bit(uint8_t &byte, int index) : byte_(byte), index_(index){};

    uint8_t &byte_;
    int index_;
  };

  Bitset() : storage{} {}

  Bit operator[](int index) { return Bit(storage[index >> 3], index & 7); }

  void serialize(BinaryBuffer &buffer) {
    buffer.write((char *) storage, sizeof(storage));
  }

private:
  uint8_t storage[(N + 7) >> 3];
};

}// namespace openao::framework::utils

#endif// OPENAO_FRAMEWORK_UTILS_BITSET_H
