
#ifndef OPENAO_UTILS_BITSET_H
#define OPENAO_UTILS_BITSET_H

#include "binarybuffer.h"
#include <cstddef>
#include <cstdint>
#include <cstring>

template<size_t N>
class Bitset {
public:
  class Bit {
  public:
    bool flip() {
      byte_ ^= (2 << (index_ - 1));
      return byte_ & (2 << (index_ - 1));
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

#endif// OPENAO_UTILS_BITSET_H
