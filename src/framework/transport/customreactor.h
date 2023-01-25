
#ifndef OPENAO_FRAMEWORK_TRANSPORT_CUSTOMREACTOR_H
#define OPENAO_FRAMEWORK_TRANSPORT_CUSTOMREACTOR_H

#include "di/dependency_injector.h"
#include "iclient.h"
#include <iostream>
#include <list>
#include <unordered_map>

using namespace openao::framework::di;

namespace openao::framework::transport {

class CustomReactor {

public:
  typedef std::function<void(IClient &, const IEvent &)> Handler;

  CustomReactor(DependencyInjector &dependency_injector)
      : dependency_injector_(dependency_injector){};

  template<typename T, typename... Services>
  void insert(void (*handler)(IClient &client, const T &t, Services...)) {
    auto lambda = [this, handler](IClient &client, const IEvent &event) {
      auto &cevent = static_cast<const T &>(event);
      auto args = std::make_tuple(
              std::ref(client), cevent,
              std::ref(dependency_injector_.get<Services>())...);
      std::apply(handler, args);
    };
    handlers_[typeid(T)].emplace_back(lambda);
  }

  template<typename T>
  void insert(void (*handler)(IClient &client, const T &t)) {
    auto lambda = [this, handler](IClient &client, const IEvent &event) {
      auto &cevent = static_cast<const T &>(event);
      auto args = std::make_tuple(std::ref(client), cevent);
      std::apply(handler, args);
    };
    handlers_[typeid(T)].emplace_back(lambda);
  }

  void react(IClient &client, IEvent &event) {
    if (handlers_.contains(typeid(event))) {
      for (auto &h: handlers_.at(typeid(event))) { h(client, event); }
    } else
      std::cout << "Reactor - There is no handler for " << typeid(event).name()
                << std::endl;
  }

private:
  std::unordered_map<std::type_index, std::list<Handler>> handlers_;
  DependencyInjector &dependency_injector_;
};

}// namespace openao::framework::transport
#endif// OPENAO_FRAMEWORK_TRANSPORT_CUSTOMREACTOR_H
