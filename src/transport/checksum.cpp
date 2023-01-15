
#include "transport/checksum.h"

uint8_t checksum(const uint8_t *data, int size) {
  uint16_t result = 0xD31Fu;

  for (int i = 0; i < (size & ~1); i += 2) {
    result ^= *(uint16_t *) (data + i);
  }

  uint32_t bitshifts = result % 16u;
  result = (result << bitshifts) | (result >> (16u - bitshifts));
  return result ^ (result >> 8u);
};