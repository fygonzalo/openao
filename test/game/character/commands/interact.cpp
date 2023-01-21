#include <gtest/gtest.h>

#include "character/commands/interact.h"

using namespace openao::game::character::commands;

TEST(character_commands_Interact, Deserialize) {

  // SETUP
  uint8_t message[] = {0x01, 0x13, 0x00, 0x00, 0x00};

  BinaryBuffer buffer;
  buffer.write((char *) message, sizeof(message));

  // EXECUTE
  auto command = buffer.read<Interact>();

  // VALIDATE
  Interact interact;
  interact.code = 1;
  interact.entity = 19;

  ASSERT_EQ(interact.code, command.code);
  ASSERT_EQ(interact.entity, command.entity);
}