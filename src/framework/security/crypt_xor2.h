
#ifndef OPENAO_FRAMEWORK_SECURITY_CRYPT_XOR2_H
#define OPENAO_FRAMEWORK_SECURITY_CRYPT_XOR2_H

#include "crypt_xor.h"

class CryptXOR2 : public CryptXOR {
public:
  /**
   * @param key Used to perform the xor operation. It is expected to be multiple
   * of 4 and up to 32 bytes. Unexpected behavior otherwise.
   */
  CryptXOR2(std::vector<char> key) : CryptXOR(key){};

  void encrypt(const char *src, char *dst, int len) override {
    CryptXOR::process(src, dst, len);
    update_key(len);
  }

  void decrypt(const char *src, char *dst, int len) override {
    CryptXOR::process(src, dst, len);
    update_key(len);
  }

private:
  void update_key(int len) {
    uint *key_ptr = (uint *) key_.data();
    for (int i = 0; i < key_.size() >> 2; i++) *(key_ptr + i) += len;
  }
};

#endif// OPENAO_FRAMEWORK_SECURITY_CRYPT_XOR2_H
