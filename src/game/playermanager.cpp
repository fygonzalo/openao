
#include "game/playermanager.h"
#include "game/messages/responses/after_spawnplayer.h"
#include "game/player.h"

namespace Game {
void PlayerManager::create(Game::Entity id, Model::Character c, Game::Player *p) {
  Messages::Responses::SpawnPlayer sp{};
  sp.entityid = id;
  sp.c = c;
  for (auto pp: players) {
    pp.second.second->write(sp);
    p->write(Messages::Responses::SpawnPlayer{.entityid = pp.first,
                                              .c = pp.second.first});
  }

  players[id] = std::pair<Model::Character, Player *>(c, p);
}

void PlayerManager::destroy(Game::Entity id) {
  players.erase(id);
}
std::pair<Model::Character, Player *>& PlayerManager::get(Entity id) {
  return players[id];
}
void PlayerManager::broadcast(const Message & message) {
  for (auto &p : players) {
    p.second.second->write(message);
  }
}

}