
#ifndef OPENAO_CHARACTERS_H
#define OPENAO_CHARACTERS_H

#include "model/character.h"
#include "model/generic.h"

namespace Model {
struct Characters {
  std::array<Character, 3> characters{0};
  std::array<Month, 3> birthday_months{0};
  std::array<Day, 3> birthday_days{0};
  std::array<Blood, 3> bloods{0};
  std::array<HP, 3> hps{0};
  std::array<MP, 3> mps{0};
  std::array<Skills, 3> skills{0};
};
}// namespace Model

#endif// OPENAO_CHARACTERS_H
