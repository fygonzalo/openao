#ifndef OPENAO_GAME_CHARACTER_IREPOSITORY_H
#define OPENAO_GAME_CHARACTER_IREPOSITORY_H

#include <cstdint>
#include <string>

#include "di/injectable.h"

#include "character/model/character.h"

namespace openao::game::character {


class IRepository : public openao::framework::di::Injectable {

public:
  virtual model::Character get(uint32_t id) = 0;
};

}// namespace openao::game::character


#endif// OPENAO_GAME_CHARACTER_IREPOSITORY_H