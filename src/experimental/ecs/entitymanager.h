
#ifndef OPENAO_EXPERIMENTAL_ECS_ENTITYMANAGER_H
#define OPENAO_EXPERIMENTAL_ECS_ENTITYMANAGER_H

#include <cstdint>
#include <queue>

namespace openao::experimental::ecs {

using Entity = std::uint32_t;

class EntityManager {
public:
  const static Entity MAX_ENTITIES = 6000;

  EntityManager() {
    for (Entity i = 0; i < MAX_ENTITIES; i++) { available_entities_.push(i); }
  }

  Entity create() {
    Entity id = available_entities_.front();
    available_entities_.pop();
    return id;
  }

  void destroy(Entity id) { available_entities_.push(id); }

private:
  std::queue<Entity> available_entities_;
};

}// namespace openao::experimental::ecs

#endif// OPENAO_EXPERIMENTAL_ECS_ENTITYMANAGER_H
