
#ifndef OPENAO_CHARACTER_REPOSITORY_H
#define OPENAO_CHARACTER_REPOSITORY_H

#include <vector>

#include "model/characters.h"

namespace Repositories {
class ICharacter {
public:
  virtual ~ICharacter() {}

  virtual Model::Characters get_characters_by_account(uint32_t account_id) = 0;

  virtual Model::Character get_character_by_id(uint32_t id) = 0;
};


}// namespace Repositories

#endif// OPENAO_CHARACTER_REPOSITORY_H
