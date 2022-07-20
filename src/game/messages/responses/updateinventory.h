
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_UPDATEINVENTORY_H
#define OPENAO_GAME_MESSAGES_RESPONSES_UPDATEINVENTORY_H

#include <vector>
#include <cstdint>

#include "model/inventoryitem.h"

namespace Game::Messages::Responses {

struct Action {
  virtual void serialize(BinaryBuffer& buffer) = 0;
};

struct AddItem : Action {
  static const uint8_t code = 1;
  Model::InventoryItem item;

  AddItem(Model::InventoryItem& i) : item(i) {}

  void serialize(BinaryBuffer& archive) override {
    Model::InventoryItem & i = item;

    archive.write(code);
    archive.set((uint8_t)0xff, 8);
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
};



struct RemoveItem : Action {
  RemoveItem(int i, uint16_t s) : character_id(i), slot(s) {}
  static const uint8_t code = 2;

  uint32_t character_id;
  uint16_t slot;

  void serialize(BinaryBuffer& buffer) override {
    buffer.write(code);
    buffer.write((uint8_t)1);
    buffer.write(character_id);
    buffer.write(slot);
  }
};



struct UpdateInventory {
  static const uint16_t type = 0x1B;

  std::vector<std::shared_ptr<Action>> actions;

  void add(const std::shared_ptr<Action>& action) {
    actions.push_back(action);
  }

  template <typename Archive>
  void serialize(Archive& archive) {
    archive.write((uint32_t) actions.size());
    for (auto &a: actions) {
      a->serialize(archive);
    }
  }

};

}

#endif// OPENAO_GAME_MESSAGES_RESPONSES_UPDATEINVENTORY_H
