
#ifndef OPENAO_FRAMEWORK_SECURITY_CIPHERSUITE_H
#define OPENAO_FRAMEWORK_SECURITY_CIPHERSUITE_H

#include <utility>

#include "crypt_xor2.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;

namespace openao::framework::security {

class CipherSet {
public:
  CipherSet(std::vector<char> key) : key_(std::move(key)), read(key_){};

  void decrypt(std::vector<char> &buffer) {
    read.decrypt(buffer.data(), buffer.data(), buffer.size());
  }

  void encrypt(std::vector<char> &buffer) {}

  void serialize(BinaryBuffer &buffer) {
    buffer.write((uint32_t) key_.size());
    buffer.write(key_.data(), key_.size());

    // Hardcoded otherwise the client may crash.

    uint8_t algo[] = {0x8b, 0x44, 0x24, 0x10, 0x56, 0x57, 0x8b, 0x7c, 0x24,
                      0x14, 0x8b, 0x70, 0x04, 0x8b, 0x00, 0x8b, 0x08, 0xb8,
                      0x00, 0x00, 0x00, 0x00, 0xc1, 0xe9, 0x02, 0xc1, 0xef,
                      0x02, 0x74, 0x27, 0x8b, 0x54, 0x24, 0x10, 0x53, 0x8d,
                      0x59, 0xff, 0x8b, 0x4c, 0x24, 0x10, 0x55, 0x8b, 0xeb,
                      0x83, 0xc1, 0x04, 0x23, 0xe8, 0x83, 0xc2, 0x04, 0x8b,
                      0x2c, 0xae, 0x33, 0x69, 0xfc, 0x40, 0x3b, 0xc7, 0x89,
                      0x6a, 0xfc, 0x72, 0xe8, 0x5d, 0x5b, 0x5f, 0x5e, 0xc3,
                      0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90};
    buffer.write((uint32_t) (sizeof(algo)));
    buffer.write((char *) algo, sizeof(algo));

    // Content lent
    buffer.write((uint32_t) (key_.size() + 4 + 4));

    // Number of Segments
    buffer.write((uint32_t) 0x01);

    // Segment length
    buffer.write((uint32_t) (key_.size()));

    // Segment data
    buffer.write(key_.data(), key_.size());
  }

private:
  std::vector<char> key_;

  CryptXOR2 read;
};

}// namespace openao::framework::security

#endif// OPENAO_FRAMEWORK_SECURITY_CIPHERSUITE_H
