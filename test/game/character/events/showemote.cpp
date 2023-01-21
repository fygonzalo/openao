#include <gtest/gtest.h>

#include "character/events/showemote.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;
using namespace openao::game::character::events;

TEST(character_events_ShowEmote, Serialize) {

  // SETUP
  ShowEmote event;
  event.entity = 1;
  event.emote = 19;

  // EXECUTE
  BinaryBuffer buffer;
  buffer.write(event);

  // VALIDATE
  uint8_t message[] = {0x01, 0x00, 0x00, 0x00, 0x13};
  ASSERT_EQ(0, std::memcmp(message, buffer.data(), sizeof(message)));
  ASSERT_EQ(sizeof(message), buffer.size());
}