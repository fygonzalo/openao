#ifndef OPENAO_TRANSPORT_SECURITY_CRYPT_XOR_H
#define OPENAO_TRANSPORT_SECURITY_CRYPT_XOR_H

#include <vector>

class CryptXOR {
public:
  /**
   * @param key Used to perform the xor operation. It is expected to be multiple
   * of 4 and up to 32 bytes. Unexpected behavior otherwise.
   */
  CryptXOR(std::vector<char> key) : key_(key){};

  virtual void encrypt(const char *src, char *dst, int len) {
    process(src, dst, len);
  }

  virtual void decrypt(const char *src, char *dst, int len) {
    process(src, dst, len);
  }

protected:
  void process(const char *src, char *dst, int len) {

    int key_len = key_.size();
    int *key_ptr = (int *)key_.data();

    int *src_ptr = (int *)src;
    int *dst_ptr = (int *)dst;

    for (int i = 0; i < len >> 2; i++) {
      *(dst_ptr + i) =
          *(src_ptr + i) ^ *(key_ptr + (i & ((key_len >> 2) - 1)));
    }
  }

  std::vector<char> key_;
};

#endif // OPENAO_TRANSPORT_SECURITY_CRYPT_XOR_H
