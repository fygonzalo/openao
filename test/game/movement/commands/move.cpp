#include <gtest/gtest.h>

#include "movement/commands/move.h"

using namespace openao::game::movement::commands;

TEST(movement_commands_Move, Deserialize) {

  // SETUP
  uint8_t message[] = {0xd0, 0x03, 0xd0, 0x03, 0x01, 0x2e,
                       0x88, 0x70, 0x04, 0x8f, 0x03};

  BinaryBuffer buffer;
  buffer.write((char *) message, sizeof(message));

  // EXECUTE
  auto command = buffer.read<Move>();

  // VALIDATE
  Move move;
  move.source = {976, 976};
  move.destination = {1136, 911};

  ASSERT_EQ(move.source.x, command.source.x);
  ASSERT_EQ(move.source.y, command.source.y);
  ASSERT_EQ(move.destination.x, command.destination.x);
  ASSERT_EQ(move.destination.y, command.destination.y);
}