
#ifndef OPENAO_EXPERIMENTAL_GAME_CHARACTER_MANAGER_H
#define OPENAO_EXPERIMENTAL_GAME_CHARACTER_MANAGER_H

#include <unordered_map>
#include <utility>

#include "experimental/game/character/character.h"
#include "experimental/transport/iclient.h"

using namespace openao::experimental::transport;

namespace openao::experimental::game::character {

class CharacterManager {
public:
  void insert(IClient& client, CharacterInfo char_info) {
    client_to_char_[&client] = std::move(char_info);
  }

  CharacterInfo& get(IClient& client) {
    return client_to_char_[&client];
  }

  void remove(IClient& client) {
    client_to_char_.erase(&client);
  }

private:

  std::unordered_map<IClient*, CharacterInfo> client_to_char_;
};

}

#endif// OPENAO_EXPERIMENTAL_GAME_CHARACTER_MANAGER_H
