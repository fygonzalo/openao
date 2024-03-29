#include <gtest/gtest.h>

#include "inventory/events/loadinventory.h"

using namespace openao::game::inventory::events;

TEST(inventory_events_LoadInventory, Serialization) {

  // SETUP
  LoadInventory event;
  event.owner = 879314;
  event.inventory_type = 1;
  auto &item = event.slots[0];
  item.id = 1748826805;
  item.timestamp = 1342614728;
  item.code = 1;
  item.quantity = 449406630;
  item.hardiness = 0;
  item.hardiness = 0;
  item.timer = 0;
  item.bind = 0;
  item.rests = 0;
  item.flags = 0;
  item.piercings = 0;
  item.intensifications = 0;


  // EXECUTE
  BinaryBuffer buffer;
  buffer.write(event);


  // VALIDATE
  uint8_t expect[] = {0x01, 0x00, 0x00, 0x00, 0x01, 0xb5, 0xfa, 0x3c, 0x68,
                      0xc8, 0xac, 0x06, 0x50, 0x01, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x01, 0xd2, 0x6a, 0x0d, 0x00, 0x00, 0x00, 0xa6,
                      0x66, 0xc9, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  ASSERT_EQ(0, std::memcmp(expect, buffer.data(), sizeof(expect)));
  ASSERT_EQ(sizeof(expect), buffer.size());
}