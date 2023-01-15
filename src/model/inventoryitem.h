
#ifndef OPENAO_MODEL_INVENTORYITEM_H
#define OPENAO_MODEL_INVENTORYITEM_H

#include <cstdint>
namespace Model {

struct Enhacement {
  /**
   * 000001: Maximum HP = 1
   * 000011: Maximum MP = 3
   * 000101: SP Lamp = 5 (multiple of 1000)
   * 000111: Maximum Weight = 7
   * 001000: Attack = 8
   * 001010: Defense = 10
   * 001011: Spell attack = 11
   * 001100: Spell defense = 12
   * 001101: Rigor = 13
   * 001110: Agility = 14
   * 001111: Movement speed = 15
   * 010000: Attack speed = 16
   * 010010: Thunderbolt attack = 18
   * 010011: Fire attack = 19
   * 010100: Ice attack = 20
   * 010101: Rotten attack = 21
   * 010110: Thunderbolt defense = 22
   * 010111: Fire defense = 23
   * 011000: Ice defense = 24
   * 011001: Rotten defense = 25
   * 011010: Stamina defense = 26
   * 011011: Soul defense = 27
   * 101000: Beating rate = 40
   * 101011: Broken = 43
   * 101100: Crashes = 44
   * 110000: Extra slots = 48
   * 111001: Collection speed = 57
   * 111010: Manufacture speed = 58
   */
  uint32_t amount{0};
  uint8_t attribute{0};
};

struct InventoryItem {

  uint32_t id;
  uint32_t creation_timestamp;
  uint8_t inventory_type;
  uint32_t entity;
  /**
   * 0: MONEY
   * 1-19: EQUIPTMENT (10 ride)
   * 20 - 44: BAG
   * 45 - 94: BAGPACK
   * 95 - ?: HIDDEN SLOT
   * 167 - 175: PD
   * 176 - 275:  FASHION BAG
   * 276 - 325: CARD BAG
   * 326 - 375: FURNITURE BAG
   */
  uint16_t slot;
  uint32_t item;
  uint32_t quantity;
  uint32_t bind{0};
  uint8_t rests{0};

  // 1 = RESTS
  // 2 = EXPIRES
  uint8_t flags{0};
  uint16_t hardiness{0};

  // Minutes if flags 2 (), Epoch if countdown
  uint32_t timer{0};
  uint8_t piercings{0};;
  uint8_t intensifications{0};

  std::array<Enhacement, 5> enhacements;
  std::array<int, 5> gems;
};

class Inventory {
public:
  void add(InventoryItem item) { inventory_.push_back(item); }

  void remove(int slot) {}

  InventoryItem &get(int slot) {
    for (auto &ii: inventory_)
      if (ii.slot == slot) { return ii; }
  }

  InventoryItem &move(int src, int dest) {
    for (auto &ii: inventory_)
      if (ii.slot == src) {
        ii.slot = dest;
        return ii;
      }
  }

  int count() {
    return inventory_.size();
  }

  std::vector<InventoryItem>::iterator begin() {
    return inventory_.begin();
  }

  std::vector<InventoryItem>::iterator end() {
    return inventory_.end();
  }

public:
  std::vector<InventoryItem> inventory_;
};

}// namespace Model

#endif// OPENAO_MODEL_INVENTORYITEM_H
