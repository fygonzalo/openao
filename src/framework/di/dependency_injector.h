
#ifndef OPENAO_FRAMEWORK_DI_DEPENDENCY_INJECTOR_H
#define OPENAO_FRAMEWORK_DI_DEPENDENCY_INJECTOR_H

#include <typeindex>
#include <unordered_map>

#include "di/injectable.h"

namespace openao::framework::di {

class DependencyInjector {
public:
  template<typename I, typename S>
  I &create(S &&s) {
    auto &idx = typeid(I);
    auto [it, ok] = injectables_.emplace(idx, std::make_unique<S>(s));
    if (!ok) throw "Type I already exists";

    return static_cast<I &>(*it->second);
  }

  template<typename S>
  S &create(S &&s) {
    auto &idx = typeid(S);
    auto [it, ok] = injectables_.emplace(idx, std::make_unique<S>(s));
    if (!ok) throw "Type S already exists";

    return static_cast<S &>(*it->second);
  }

  template<typename I>
  I &get() {
    auto &index = typeid(I);
    return static_cast<I &>(*injectables_.at(index));
  }

private:
  std::unordered_map<std::type_index, std::unique_ptr<Injectable>> injectables_;
};

}// namespace openao::framework::di

#endif// OPENAO_FRAMEWORK_DI_DEPENDENCY_INJECTOR_H
