
#ifndef OPENAO_GAME_PLAYERMANAGER_H
#define OPENAO_GAME_PLAYERMANAGER_H

#include "entitymanager.h"
#include "game/messages/responses/spawnplayer.h"
#include "model/character.h"
#include "transport/message.h"
#include <map>

namespace Game {
class Player;
class PlayerManager {

public:
  void create(Entity id, Model::Character c, Player *p);

  void destroy(Entity id);

  void broadcast(const Message &message);

  std::pair<Model::Character, Player *> &get(Entity id);

private:
  std::map<Entity, std::pair<Model::Character, Player *>> players;
};

}// namespace Game

#endif// OPENAO_GAME_PLAYERMANAGER_H
