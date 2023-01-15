
#ifndef OPENAO_GAME_MESSAGES_INVENTORY_EVENT_H
#define OPENAO_GAME_MESSAGES_INVENTORY_EVENT_H

#include "model/inventoryitem.h"
#include "utils/binarybuffer.h"

#include <cstdint>
#include <vector>

namespace Game::Messages::Responses {

struct InventoryEvent {

  struct Event {
    enum class Type : uint8_t {
      ADD = 1,
      REMOVE = 2,
    };

    virtual void serialize(BinaryBuffer &buffer) = 0;
  };

  struct Add : Event {

    Model::InventoryItem inventory_item_;

    Add(Model::InventoryItem inventory_event)
        : inventory_item_(inventory_event){};

    void serialize(BinaryBuffer &buffer) override {
      buffer.write((uint8_t) Type::ADD);
      buffer.write(inventory_item_.id);
      buffer.write(inventory_item_.creation_timestamp);
      buffer.write(inventory_item_.item);
      buffer.set(0, 20);
      buffer.write(inventory_item_.inventory_type);
      buffer.write(inventory_item_.entity);
      buffer.write(inventory_item_.slot);
      buffer.write(inventory_item_.quantity);
      buffer.write((uint8_t) 0);
      buffer.write(inventory_item_.hardiness);
      buffer.write(inventory_item_.timer);
      buffer.write((uint16_t) 0);
      buffer.write(inventory_item_.bind);
      buffer.write(inventory_item_.rests);
      buffer.write(inventory_item_.flags);
      buffer.write((uint16_t) 0);
      buffer.set(0, 20);
      buffer.write((uint8_t) 0);
      buffer.write(inventory_item_.piercings);
      buffer.write(inventory_item_.intensifications);
      buffer.write((uint16_t) 0);
    }
  };

  struct Remove : Event {

    uint8_t inventory_type_;
    uint32_t entity_;
    uint16_t slot_;

    Remove(uint8_t inventory_type, uint32_t entity, uint16_t slot)
        : inventory_type_(inventory_type), entity_(entity), slot_(slot){};

    void serialize(BinaryBuffer &buffer) override {
      buffer.write((uint8_t) Type::REMOVE);
      buffer.write(inventory_type_);
      buffer.write(entity_);
      buffer.write(slot_);
    }
  };

  static const uint16_t type = 27;

  void serialize(BinaryBuffer &buffer) {
    buffer.write((uint32_t) events.size());
    for (auto &e: events) { e->serialize(buffer); };
  }

  std::vector<std::unique_ptr<Event>> events{};
};

}// namespace Game::Messages::Responses

#endif// OPENAO_GAME_MESSAGES_INVENTORY_EVENT_H
