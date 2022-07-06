
#ifndef OPENAO_CHARACTER_REPOSITORY_H
#define OPENAO_CHARACTER_REPOSITORY_H

#include <vector>

#include "model/characters.h"

namespace Repositories {
class ICharacter {
public:
  virtual Model::Characters get_characters_by_account(uint32_t account_id) = 0;
};


}// namespace Repositories

#endif// OPENAO_CHARACTER_REPOSITORY_H
