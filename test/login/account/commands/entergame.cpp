#include <gtest/gtest.h>

#include "account/commands/entergame.h"

using namespace openao::login::account::commands;

TEST(account_commands_EnterGame, Deserialize) {

  // TODO: what happens when the client sends a dirty buffer? for example in the
  // pin, when the account doesn't have pin.

  // SETUP
  uint8_t event[] = {0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  BinaryBuffer buffer{};
  buffer.write((char *) event, sizeof(event));

  // EXECUTE
  EnterGame command = buffer.read<EnterGame>();

  // VALIDATE
  EnterGame expect;
  expect.character_index = 0;
  expect.branch = 1;
  expect.pin = "";

  ASSERT_EQ(expect.character_index, command.character_index);
  ASSERT_EQ(expect.branch, command.branch);
  ASSERT_EQ(expect.pin, command.pin);
}