#ifndef OPENAO_GAME_IVENTORY_MODEL_ITEM_H
#define OPENAO_GAME_IVENTORY_MODEL_ITEM_H

#include <cstdint>

namespace openao::game::inventory::model {

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

}// namespace openao::game::inventory::model

#endif// OPENAO_GAME_IVENTORY_MODEL_ITEM_H