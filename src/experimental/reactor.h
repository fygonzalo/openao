
#ifndef OPENAO_EXPERIMENTAL_REACTOR_H
#define OPENAO_EXPERIMENTAL_REACTOR_H

#include "experimental/reactor/event.h"

#include "utils/binarybuffer.h"

#include <cstdint>
#include <functional>
#include <map>
#include <typeindex>

#include <memory>

namespace openao::experimental {

class Reactor {

public:

  template <class T>
  void add(std::function<void(const T& t)> fun) {
    handlers_[typeid(T)] = [fun](const reactor::IEvent& e) {
      fun(static_cast<const T&>(e));
    };
  }

  template <class T>
  void react(const T& t) {
    std::type_index index = typeid(T);
    if (!handlers_.contains(index))
      return;

    handlers_.at(index)(t);
  }

  void react(std::type_index index, reactor::IEvent& e) {
    handlers_.at(index)(e);
  }

private:
  std::map<std::type_index, std::function<void(const reactor::IEvent& e)>> handlers_{};
};

}// namespace openao::experimental

#endif// OPENAO_EXPERIMENTAL_REACTOR_H

