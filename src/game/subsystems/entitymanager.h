
#ifndef OPENAO_GAME_SUBSYSTEMS_ENTITYMANAGER_H
#define OPENAO_GAME_SUBSYSTEMS_ENTITYMANAGER_H

#include <map>

#include "model/character.h"
#include "model/inventoryitem.h"

#include "transport/messagestream.h"

namespace Game::Subsystems {

struct Entity {
  uint32_t id;
  MessageStream *stream;
  Model::Character character;
  Model::Inventory items;
};

class EntityManager {
private:
  std::vector<Entity> entities_;

public:
  void insert(Entity &e) {
    e.id =  entities_.size() + 1;
    entities_.push_back(e);
  }

  std::vector<Entity> &get_all() { return entities_; }

  Entity& find_by_character_id(int id) {
    for (Entity& e : entities_) {
      if (e.character.id == id)
        return e;
    }
  }


};

}// namespace Game::Subsystems

#endif// OPENAO_GAME_SUBSYSTEMS_ENTITYMANAGER_H
