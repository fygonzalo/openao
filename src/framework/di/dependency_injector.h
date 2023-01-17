
#ifndef OPENAO_FRAMEWORK_DI_DEPENDENCY_INJECTOR_H
#define OPENAO_FRAMEWORK_DI_DEPENDENCY_INJECTOR_H

#include <typeindex>
#include <unordered_map>

namespace openao::framework::di {

class DependencyInjector {
public:
  template<typename T>
  T &create() {
    auto &idx = typeid(T);
    auto [it, ok] = injectables_.emplace(idx, T());
    if (!ok) throw "Type T already exists";

    return std::any_cast<T &>(it->second);
  }

  template<typename T, typename... Args>
  T &create(auto &&...args) {
    auto &idx = typeid(T);
    auto [it, ok] = injectables_.emplace(idx, T(args...));
    if (!ok) throw "Type T already exists";

    return std::any_cast<T &>(it->second);
  }

  template<typename T>
  T &get() {
    auto &index = typeid(T);
    return std::any_cast<T &>(injectables_.at(index));
  }

private:
  std::unordered_map<std::type_index, std::any> injectables_;
};

}// namespace openao::framework::di

#endif// OPENAO_FRAMEWORK_DI_DEPENDENCY_INJECTOR_H