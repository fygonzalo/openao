#ifndef OPENAO_GAME_INVENTORY_REPOSITORIES_IINVENTORYREPOSITORY_H
#define OPENAO_GAME_INVENTORY_REPOSITORIES_IINVENTORYREPOSITORY_H

#include <cstdint>
#include <list>

#include "di/injectable.h"

namespace openao::game::inventory::repositories {

struct Item {
  uint32_t id;
  uint32_t timestamp;
  uint8_t type;
  uint32_t entity;
  uint16_t slot;
  uint32_t item;
  uint32_t quantity;
  uint32_t bind;
  uint8_t rests;

  uint8_t flags;
  uint16_t hardiness;
  uint32_t timer;
  uint8_t piercings;
  uint8_t intensifications;
};


class IInventoryRepository : public openao::framework::di::Injectable {
public:
  virtual ~IInventoryRepository() = default;

  virtual std::list<Item> get(uint32_t type, uint32_t entity) = 0;
};

}// namespace openao::game::inventory::repositories

#endif// OPENAO_GAME_INVENTORY_REPOSITORIES_IINVENTORYREPOSITORY_H