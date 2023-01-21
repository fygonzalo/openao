#include <gtest/gtest.h>

#include "movement/events/move.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;
using namespace openao::game::movement::events;

TEST(movement_events_Move, Serialize) {

  // SETUP
  Move event;
  event.entity = 3412330713;
  event.source.x = 8176;
  event.source.y = 2448;
  event.destination.x = 7728;
  event.destination.y = 2543;
  event.speed = 104;

  // EXECUTE
  BinaryBuffer buffer;
  buffer.write(event);

  // VALIDATE
  uint8_t message[] = {0xd9, 0x08, 0x64, 0xcb, 0xf0, 0x1f, 0x00, 0x00,
                       0x90, 0x09, 0x00, 0x00, 0x30, 0x1e, 0x00, 0x00,
                       0xef, 0x09, 0x00, 0x00, 0x68, 0x00};
  ASSERT_EQ(0, std::memcmp(message, buffer.data(), sizeof(message)));
  ASSERT_EQ(sizeof(message), buffer.size());
}