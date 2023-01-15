
#ifndef OPENAO_DATASOURCES_CHARACTER_H
#define OPENAO_DATASOURCES_CHARACTER_H

#include <vector>

#include "model/characters.h"

namespace Datasources {
class ICharacter {
public:
  virtual ~ICharacter() {}

  virtual Model::Characters get_characters_by_account(uint32_t account_id) = 0;

  virtual Model::Character get_character_by_id(uint32_t id) = 0;

  virtual void update_character(Model::Character &character) = 0;
};


}// namespace Datasources

#endif// OPENAO_DATASOURCES_CHARACTER_H
