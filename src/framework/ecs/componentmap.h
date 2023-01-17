
#ifndef OPENAO_FRAMEWORK_ECS_COMPONENTMAP_H
#define OPENAO_FRAMEWORK_ECS_COMPONENTMAP_H

#include <map>

#include "entitymanager.h"

namespace openao::framework::ecs {

class AbstractComponentMap {
public:
  virtual ~AbstractComponentMap() = default;
  virtual void remove(Entity entity) = 0;
};

template<typename T>
class ComponentMap : public AbstractComponentMap {

public:
  void insert(Entity entity, T t) {
    components_[entity] = t;
    T &tt = components_[entity];
    reverse_[&tt] = entity;
  }

  T &operator[](Entity entity) { return components_.at(entity); }

  Entity reverse(const T &t) { return reverse_.at(&t); }

  void remove(Entity entity) override { components_.erase(entity); }

private:
  std::map<Entity, T> components_;
  std::map<const T *, Entity> reverse_;
};

}// namespace openao::framework::ecs

#endif// OPENAO_FRAMEWORK_ECS_COMPONENTMAP_H
