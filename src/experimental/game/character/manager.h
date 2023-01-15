
#ifndef OPENAO_EXPERIMENTAL_GAME_CHARACTER_MANAGER_H
#define OPENAO_EXPERIMENTAL_GAME_CHARACTER_MANAGER_H

#include <unordered_map>
#include <utility>

#include "experimental/game/character/character.h"
#include "experimental/client.h"

namespace openao::experimental::game::character {

class CharacterManager {
public:
  void insert(Client& client, CharacterInfo char_info) {
    client_to_char_[&client] = std::move(char_info);
  }

  CharacterInfo& get(Client& client) {
    return client_to_char_[&client];
  }

  void remove(Client& client) {
    client_to_char_.erase(&client);
  }

private:

  std::unordered_map<Client*, CharacterInfo> client_to_char_;
};

}

#endif// OPENAO_EXPERIMENTAL_GAME_CHARACTER_MANAGER_H
