
#ifndef OPENAO_EXPERIMENTAL_DI_INJECTOR_H
#define OPENAO_EXPERIMENTAL_DI_INJECTOR_H

#include <typeindex>
#include <unordered_map>

#include "experimental/di/injectable.h"

namespace openao::experimental::di {


class Injector {
public:
  template<typename T>
  void insert(T &t) {
    injectables_[typeid(T)] = &t;
  }

  template<typename T>
  auto get() {
    auto &index = typeid(T);
    return (T&)(injectables_[index]);
  }

private:
  std::unordered_map<std::type_index, Injectable *> injectables_;
};

}// namespace openao::experimental::di

#endif// OPENAO_EXPERIMENTAL_DI_INJECTOR_H
