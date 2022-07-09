
#ifndef OPENAO_MODEL_BAGITEM_H
#define OPENAO_MODEL_BAGITEM_H

#include <cstdint>
namespace Model {

struct BagItem {

  uint32_t id;
  uint32_t character_id;
  uint16_t slot;
  uint32_t item_id;
  uint32_t quantity;

};

}

#endif// OPENAO_MODEL_BAGITEM_H
