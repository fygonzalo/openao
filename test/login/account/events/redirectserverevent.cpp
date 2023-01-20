#include <gtest/gtest.h>

#include "account/events/redirectserverevent.h"

using namespace openao::login::account::events;

TEST(RedirectServerEvent, Serialize) {

  // SETUP
  RedirectServerEvent event;
  event.session = 1;
  event.ip = "127.0.0.1";
  event.port = 30001;

  // EXECUTE
  BinaryBuffer result;
  result.write(event);

  // VALIDATE
  uint8_t expect[] = {0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x31,
                      0x32, 0x37, 0x2e, 0x30, 0x2e, 0x30, 0x2e, 0x31,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x31,
                      0x75, 0x00, 0x00, 0x00, 0x00, 0x00};

  ASSERT_EQ(0, std::memcmp(expect, result.data(), sizeof(expect)));
}