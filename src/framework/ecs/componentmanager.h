
#ifndef OPENAO_FRAMEWORK_ECS_COMPONENTMANAGER_H
#define OPENAO_FRAMEWORK_ECS_COMPONENTMANAGER_H

#include <map>
#include <typeindex>
#include <typeinfo>
#include <unordered_set>

#include "componentmap.h"
#include "entitymanager.h"

namespace openao::framework::ecs {

using ComponentType = std::type_index;

class ComponentManager {
public:
  template<typename T>
  void add(Entity entity, T t) {
    get<T>().insert(entity, t);
  }

  template<typename T>
  T &get(Entity entity) {
    return get<T>()[entity];
  }


private:
  template<typename T>
  ComponentMap<T> &get() {
    ComponentType type = typeid(T);
    if (!component_vectors_.contains(type)) {
      component_vectors_[type] = std::make_unique<ComponentMap<T>>();
    }
    auto &abstract_map = component_vectors_.at(type);
    auto &concrete_map = static_cast<ComponentMap<T> &>(*abstract_map.get());

    return concrete_map;
  }

  std::unordered_set<ComponentType> component_types_;
  std::map<ComponentType, std::unique_ptr<AbstractComponentMap>>
          component_vectors_;
};

}// namespace openao::framework::ecs

#endif// OPENAO_FRAMEWORK_ECS_COMPONENTMANAGER_H
