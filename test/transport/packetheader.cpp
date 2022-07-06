#include <gtest/gtest.h>

#include "transport/binarybuffer.h"
#include "transport/packetheader.h"

TEST(PacketHeader, Serialization) {
  BinaryBuffer buffer;

  PacketHeader header{};
  header.size = 20;
  header.sequence = -1;
  header.flags = 0;
  header.checksum = 0;

  header.serialize(buffer);

  EXPECT_EQ(buffer.size(), 6);
}
