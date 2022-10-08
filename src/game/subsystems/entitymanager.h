
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
  int id_ = 1;

public:
  void insert(Entity &e) {
    e.id = id_++;
    entities_.push_back(e);
  }

  std::vector<Entity> &get_all() { return entities_; }

  Entity& find_by_character_id(int id) {
    for (Entity& e : entities_) {
      if (e.character.id == id)
        return e;
    }
  }

  Entity& find_by_stream(MessageStream& stream) {
    for (Entity& e : entities_) {
      if (e.stream == &stream)
        return e;
    }
  }

  Entity& remove_by_stream(MessageStream& stream) {
    int i = 0;
    for (Entity& e : entities_) {
      if (e.stream == &stream) {
        entities_.erase(entities_.begin() + i);
        return e;
      }
      i++;
    }
  }

};

}// namespace Game::Subsystems

#endif// OPENAO_GAME_SUBSYSTEMS_ENTITYMANAGER_H
