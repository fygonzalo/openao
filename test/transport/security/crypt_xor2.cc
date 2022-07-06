#include <gtest/gtest.h>

#include "transport/security/crypt_xor2.h"

TEST(CryptXOR2, successfull_encryption_when_content_multiple_of_4) {

  std::vector<char> key{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

  std::vector<char> data{0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                         0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};

  CryptXOR2 crypt_xor2(key);
  crypt_xor2.encrypt(data.data(), data.data(), data.size());

  // Expect the result is equal to the following vector
  std::vector<char> result{0x01, 0x00, 0x03, 0x02, 0x01, 0x01, 0x01, 0x01,
                           0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};
  EXPECT_EQ(true, data == result);
}