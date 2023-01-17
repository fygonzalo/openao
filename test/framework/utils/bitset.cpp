#include <gtest/gtest.h>

#include "utils/bitset.h"

using openao::framework::utils::Bitset;

TEST(Bitset, Flip) {

  Bitset<8> bitset;
  bitset[0].flip();
  EXPECT_EQ(true, bitset[0]);
}