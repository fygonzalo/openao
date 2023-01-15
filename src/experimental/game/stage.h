
#ifndef OPENAO_EXPERIMENTAL_GAME_STAGE_H
#define OPENAO_EXPERIMENTAL_GAME_STAGE_H

#include "experimental/game/character/manager.h"

namespace openao::experimental::game {

class Stage {
public:
  Stage(character::CharacterManager &character_manager)
      : character_manager_(character_manager){};

  void join(IClient &client) {
    auto character = character_manager_.get(client);
    for (auto &c: clients_) { auto c_ = character_manager_.get(*c); }
    // Spawn myself to others
    // Spawn others to myself
    clients_.emplace(&client);
  };

  void leave(IClient &client) {
    // Delete myself to others
    clients_.erase(&client);
  }

  void broadcast(reactor::IEvent &event) {
    for (auto &c: clients_) c->send(event);
  }

private:
  std::unordered_set<IClient *> clients_;

  character::CharacterManager &character_manager_;
};

}// namespace openao::experimental::game

#endif// OPENAO_EXPERIMENTAL_GAME_STAGE_H
