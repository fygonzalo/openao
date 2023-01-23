#ifndef OPENAO_GAME_CHARACTER_MANAGER_H
#define OPENAO_GAME_CHARACTER_MANAGER_H

#include <unordered_map>

#include "di/injectable.h"
#include "transport/iclient.h"

using namespace openao::framework::transport;

namespace openao::game::character {

class Manager : public openao::framework::di::Injectable {
public:
  void insert(IClient *client, uint32_t character_id) {
    client_to_char_[client] = character_id;
    char_to_client_[character_id] = client;
  }

  uint32_t get(IClient *client) {
    if (client_to_char_.contains(client)) return client_to_char_.at(client);

    return -1;
  }

  IClient *get(uint32_t character_id) {
    if (char_to_client_.contains(character_id))
      return char_to_client_.at(character_id);

    return nullptr;
  }


  void remove(IClient *client) {
    auto r = client_to_char_.find(client);
    if (r == client_to_char_.end()) return;

    auto key = client_to_char_.at(client);
    char_to_client_.erase(key);
    client_to_char_.erase(client);
  }

private:
  std::unordered_map<IClient *, uint32_t> client_to_char_{};
  std::unordered_map<uint32_t, IClient *> char_to_client_{};
};

}// namespace openao::game::character


#endif// OPENAO_GAME_CHARACTER_MANAGER_H