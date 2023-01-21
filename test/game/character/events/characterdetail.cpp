#include <gtest/gtest.h>

#include "character/events/characterdetail.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;
using namespace openao::game::character::events;

TEST(character_events_CharacterDetail, Serialize) {
  CharacterDetail event;

  BinaryBuffer buffer;
  buffer.write(event);

  EXPECT_EQ(4118, buffer.size());
}