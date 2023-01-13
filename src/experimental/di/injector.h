
#ifndef OPENAO_EXPERIMENTAL_DI_INJECTOR_H
#define OPENAO_EXPERIMENTAL_DI_INJECTOR_H

#include <typeindex>
#include <unordered_map>

#include "experimental/di/injectable.h"

namespace openao::experimental::di {


class Injector {
public:
  template<typename T, typename ...Args>
  auto create(Args... args) {
    injectables_[typeid(T)] = std::make_unique<T>(args...);
    return static_cast<T &>(*injectables_.at(typeid(T)));
  }

  template<typename T>
  T &get() {
    auto &index = typeid(T);
    return static_cast<T &>(*injectables_[index]);
  }

private:
  std::unordered_map<std::type_index, std::unique_ptr<Injectable>> injectables_;
};

}// namespace openao::experimental::di

#endif// OPENAO_EXPERIMENTAL_DI_INJECTOR_H
