#ifndef OPENAO_GAME_INVENTORY_IREPOSITORY_H
#define OPENAO_GAME_INVENTORY_IREPOSITORY_H

#include <cstdint>
#include <list>

#include "di/injectable.h"

#include "inventory/model/item.h"

namespace openao::game::inventory {


class IRepository : public openao::framework::di::Injectable {
public:
  virtual ~IRepository() = default;

  virtual std::list<model::Item> get(uint32_t type, uint32_t entity) = 0;
};

}// namespace openao::game::inventory

#endif// OPENAO_GAME_INVENTORY_IREPOSITORY_H