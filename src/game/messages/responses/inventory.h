
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_INVENTORY_H
#define OPENAO_GAME_MESSAGES_RESPONSES_INVENTORY_H

#include <vector>

#include "model/inventoryitem.h"

namespace Game::Messages::Responses {

struct Inventory {

  static const uint16_t type = 0x1A;

  std::vector<Model::InventoryItem> items;

  template<typename Archive>
  void serialize(Archive &archive) {
    archive.write((uint32_t) items.size());
    for (auto &i: items) {
      // Operation
      // 1: Add item
      // 2: Remove item
      archive.set(1, 1);
      archive.set(0xff, 8);
      archive.write(i.item_id);
      for (auto& e: i.enhacements) {
        archive.write(((uint32_t)e.attribute << 26) | e.amount);
      }
      archive.set(1, 1);
      archive.write(i.character_id);
      archive.write(i.slot);
      archive.write(i.quantity);
      archive.set(0, 8);
      archive.set(0, 1);
      archive.write(i.owner_id);
      archive.write(i.rests);
      archive.write(i.rests_enabled);
      archive.set(0, 2);
      archive.set(0, 20);
      archive.set(0, 5);
    }
  }
};

}// namespace Game::Messages::Responses

#endif// OPENAO_GAME_MESSAGES_RESPONSES_INVENTORY_H
