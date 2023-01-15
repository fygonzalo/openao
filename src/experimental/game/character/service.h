
#ifndef OPENAO_EXPERIMENTAL_GAME_CHARACTER_SERVICE_H
#define OPENAO_EXPERIMENTAL_GAME_CHARACTER_SERVICE_H

#include "experimental/game/character/character.h"

namespace openao::experimental::game::character {

class CharacterService {
public:
  CharacterInfo get_by_character_id(uint32_t id) {
    return CharacterInfo{.name = "openao"};
  }

};

}

#endif// OPENAO_EXPERIMENTAL_GAME_CHARACTER_SERVICE_H
