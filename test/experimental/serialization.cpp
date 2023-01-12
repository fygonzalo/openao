#include <gtest/gtest.h>

#include <typeindex>
#include <typeinfo>

#include "experimental/game/chat/chatmessageevent.h"
#include "experimental/reactor/event.h"
#include "experimental/serialization/serializer.h"

using namespace openao::experimental;
using namespace openao::experimental::game::chat;
using namespace openao::experimental::serialization;

TEST(Serialization, Serialization_Message_Test) {
  ChatMessageEvent command;
  command.entity = 1;
  command.name = "Ciborg";
  command.text = "Hello world!";

  Serializer serializer;
  serializer.insert<ChatMessageEvent>(23);

  uint8_t data[] = {0x17, 0x00, 0x01, 0x00, 0x00, 0x00, 0x43, 0x69, 0x62,
                    0x6f, 0x72, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x65, 0x6c, 0x6c,
                    0x6f, 0x20, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x21, 0x00};

  auto buffer = serializer.serialize(command);

  EXPECT_EQ(0, std::memcmp(data, buffer.data(), sizeof(data)));
}