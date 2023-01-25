#ifndef OPENAO_GAME_INVENTORY_MODEL_INVENTORY_H
#define OPENAO_GAME_INVENTORY_MODEL_INVENTORY_H


#include <cstdint>
#include <unordered_map>

namespace openao::game::inventory::model {

struct Slot {

  uint32_t id{0};
  uint32_t timestamp{0};
  uint32_t code{0};
  uint32_t quantity{0};
  uint32_t bind{0};
  uint8_t rests{0};
  uint8_t flags{0};
  uint16_t hardiness{0};
  uint32_t timer{0};
  uint8_t piercings{0};
  uint8_t intensifications{0};

  operator bool() const { return code != 0; }

  operator uint32_t() const { return code; }
};

class Inventory : public framework::IEvent {
public:
  std::pair<uint16_t, Slot &> operator[](uint16_t slot) {
    return {slot, inventory_[slot]};
  }

  void move(uint16_t from, uint16_t to) {
    auto i1 = inventory_[from];
    auto i2 = inventory_[to];
    inventory_[from] = i2;
    inventory_[to] = i1;
  }

  auto all() const { return inventory_; }

private:
  std::unordered_map<uint16_t, Slot> inventory_;
};

}// namespace openao::game::inventory::model
#endif// OPENAO_GAME_INVENTORY_MODEL_INVENTORY_H
