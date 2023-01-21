#ifndef OPENAO_GAME_INVENTORY_EVENTS_LOADINVENTORY_H
#define OPENAO_GAME_INVENTORY_EVENTS_LOADINVENTORY_H

#include <list>

#include "event.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;

namespace openao::game::inventory::events {

struct LoadInventory : framework::IEvent {

  enum class INVENTORIES : uint8_t {
    BAG = 1,
    PERSONAL_BANK = 2,
    GUILD_BANK = 3
  };

  struct Item {

    uint32_t id;
    uint32_t timestamp;
    uint8_t type;
    uint32_t entity;
    uint16_t slot;
    uint32_t code;
    uint32_t quantity;
    uint32_t bind;
    uint8_t rests;

    uint8_t flags;
    uint16_t hardiness;
    uint32_t timer;
    uint8_t piercings;
    uint8_t intensifications;

    void serialize(BinaryBuffer &buffer) {
      buffer.write(id);
      buffer.write(timestamp);
      buffer.write(code);
      buffer.set(0, 20);
      buffer.write(type);
      buffer.write(entity);
      buffer.write(slot);
      buffer.write(quantity);
      buffer.set(0, 1);
      buffer.write(hardiness);
      buffer.write(timer);
      buffer.write(0);
      buffer.write(bind);
      buffer.write(rests);
      buffer.write(flags);
      buffer.set(0, 2);
      buffer.set(0, 20);
      buffer.set(0, 1);
      buffer.write(piercings);
      buffer.write(intensifications);
    }
  };

  std::list<Item> items;

  void serialize(BinaryBuffer &buffer) {
    buffer.write((uint32_t) items.size());
    for (auto &i: items) {
      buffer.write((uint8_t) 1);
      buffer.write(i);
    }
  }
};

}// namespace openao::game::inventory::events


#endif// OPENAO_GAME_INVENTORY_EVENTS_LOADINVENTORY_H