#include <gtest/gtest.h>

#include "character/commands/authenticatecommand.h"

using namespace openao::game::character::commands;

TEST(AuthenticateCommand, Deserialize) {

  // SETUP
  uint8_t event[] = {0xab, 0x4e, 0x81, 0x7a, 0x7e, 0x6c, 0x2e, 0xf4, 0x19,
                     0x6e, 0x9d, 0xef, 0xa0, 0xff, 0xe4, 0x85, 0x55, 0x0d,
                     0xc5, 0x2a, 0x00, 0xd2, 0x6a, 0x0d, 0x00, 0x50, 0x00,
                     0x00, 0x00, 0x05, 0xc7, 0x20, 0x4f};

  BinaryBuffer buffer;
  buffer.write((char *) event, sizeof(event));

  // EXECUTE
  auto result = buffer.read<AuthenticateCommand>();

  // VALIDATE
  AuthenticateCommand expect{};
  expect.account_id = 2802957;
  expect.character_id = 879314;
  expect.stage = 80;
  expect.session_id = 1327548165;

  // TODO: validate the version.
  EXPECT_EQ(expect.account_id, result.account_id);
  EXPECT_EQ(expect.character_id, result.character_id);
  EXPECT_EQ(expect.stage, result.stage);
  EXPECT_EQ(expect.session_id, result.session_id);
}