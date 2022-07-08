
#ifndef OPENAO_CIPHERSUITE_H
#define OPENAO_CIPHERSUITE_H

#include <utility>

#include "utils/binarybuffer.h"

#include "transport/security/crypt_xor2.h"

class CipherSet {
public:
  CipherSet(std::vector<char> key) : key_(std::move(key)), read(key_){};

  void decrypt(std::vector<char> &buffer) {read.decrypt(buffer.data(), buffer.data(), buffer.size());}

  void encrypt(std::vector<char> &buffer) {}

  void serialize(BinaryBuffer &buffer) {
    buffer.write((uint32_t) key_.size());
    buffer.write(key_.data(), key_.size());
  }

private:
  std::vector<char> key_;

  CryptXOR2 read;


};


#endif// OPENAO_CIPHERSUITE_H
