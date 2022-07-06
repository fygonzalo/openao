
#ifndef OPENAO_CIPHERSUITE_H
#define OPENAO_CIPHERSUITE_H

#include <utility>

#include "transport/binarybuffer.h"

class CipherSet {
public:
  CipherSet(std::vector<char> key) : key_(std::move(key)){};

  void decrypt(std::vector<char> &buffer) {}

  void encrypt(std::vector<char> &buffer) {}

  void serialize(BinaryBuffer &buffer) {
    buffer.write((uint32_t) key_.size());
    buffer.write(key_.data(), key_.size());
  }

private:
  std::vector<char> key_;
};


#endif// OPENAO_CIPHERSUITE_H
