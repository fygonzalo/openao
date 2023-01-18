#include <gtest/gtest.h>

#include "account/events/autherrorevent.h"

using namespace openao::login::account::events;

TEST(AuthErrorEvent, Serialize) {

  // SETUP
  AuthErrorEvent event;
  event.message_code = 152;

  // EXECUTE
  BinaryBuffer result;
  result.write(event);

  // VALIDATE
  uint8_t expect[] = {0x98, 0x00, 0x00, 0x00};

  ASSERT_EQ(0, std::memcmp(expect, result.data(), sizeof(expect)));
}