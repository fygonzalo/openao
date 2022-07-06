
#ifndef OPENAO_REPOSITORIES_IMPL_MEMORY_CHARACTER_H
#define OPENAO_REPOSITORIES_IMPL_MEMORY_CHARACTER_H

#include <cstdint>

#include "repositories/icharacter.h"

namespace Repositories::Memory {
  class Character : public ICharacter {
  public:
    Model::Characters
    get_characters_by_account(uint32_t account_id) override {
      Model::Character character{};

      character.id = 1;
      character.name = "Ciborg";
      character.title = "AFK";
      character.faction = 1;
      character.level = 10;
      character.stage = 41;

      character.account_id = 1;
      character.account_username = "gonzalo";

      character.attributes.gender = 1;
      character.attributes.height = 0;
      character.attributes.hair_style = 0;
      character.attributes.hair_color = 0;
      character.attributes.skin_color = 0;

      character.stats.hp_current = 100;
      character.stats.mp_current = 1001;

      character.equipment.head = 6179;
      character.equipment.body = 6180;
      character.equipment.main_hand = 0;
      character.equipment.off_hand = 0;
      character.equipment.hand = 0;
      character.equipment.feet = 6181;
      character.equipment.back = 0;
      character.equipment.ride = 6795;

      Model::Characters characters;
      characters.slots = 3;
      characters.characters[0] = character;

      return characters;
    }
  };
}// namespace Repositories::Memory

#endif// OPENAO_REPOSITORIES_IMPL_MEMORY_CHARACTER_H
