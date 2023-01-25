#ifndef OPENAO_GAME_INVENTORY_EVENTS_UPDATEINVENTORY_H
#define OPENAO_GAME_INVENTORY_EVENTS_UPDATEINVENTORY_H

#include <list>

#include "event.h"
#include "utils/binarybuffer.h"

#include "inventory/model/inventory.h"

using namespace openao::framework::utils;

namespace openao::game::inventory::events {

struct UpdateInventory : framework::IEvent {

  uint8_t inventory_type;
  uint32_t owner;
  std::unordered_map<uint16_t, model::Slot> slots;

  void serialize(BinaryBuffer &buffer) {
    buffer.write((uint32_t) slots.size());
    for (auto &[pos, slot]: slots) {
      bool empty = slot.code == 0;
      uint8_t operation = empty ? 2 : 1;
      buffer.write(operation);

      if (!empty) {
        buffer.write(slot.id);
        buffer.write(slot.timestamp);
        buffer.write(slot.code);
        buffer.set(0, 20);
      }

      buffer.write(inventory_type);
      buffer.write(owner);
      buffer.write(pos);

      if (!empty) {
        buffer.write(slot.quantity);
        buffer.set(0, 1);
        buffer.write(slot.hardiness);
        buffer.write(slot.timer);
        buffer.write(0);
        buffer.write(slot.bind);
        buffer.write(slot.rests);
        buffer.write(slot.flags);
        buffer.set(0, 2);
        buffer.set(0, 20);
        buffer.set(0, 1);
        buffer.write(slot.piercings);
        buffer.write(slot.intensifications);
      }
    }
  }
};

}// namespace openao::game::inventory::events

#endif// OPENAO_GAME_INVENTORY_EVENTS_UPDATEINVENTORY_H
