
#ifndef OPENAO_GAME_ENTITYMANAGER_H
#define OPENAO_GAME_ENTITYMANAGER_H

#include <cstdint>
#include <queue>

namespace Game {

using Entity = std::uint32_t;

class EntityManager {
public:
  EntityManager() {
    for (Entity entity = 1; entity < 65000; ++entity)
    {
      entities.push(entity);
    }

  }

  Entity create() {
    Entity id = entities.front();
    entities.pop();
    return id;
  }

  void destroy(Entity id) {
    entities.push(id);
  }

private:
  std::queue<Entity> entities{};
};

}

#endif// OPENAO_GAME_ENTITYMANAGER_H
