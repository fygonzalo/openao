#include <gtest/gtest.h>

#include "character/events/characterdetailevent.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;
using namespace openao::game::character::events;

TEST(CharacterDetailEvent, Serialize) {
  CharacterDetailEvent event;

  BinaryBuffer buffer;
  buffer.write(event);

  EXPECT_EQ(4118, buffer.size());
}