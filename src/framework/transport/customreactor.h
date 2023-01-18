
#ifndef OPENAO_FRAMEWORK_TRANSPORT_CUSTOMREACTOR_H
#define OPENAO_FRAMEWORK_TRANSPORT_CUSTOMREACTOR_H

#include "di/dependency_injector.h"
#include "iclient.h"

using namespace openao::framework::di;

namespace openao::framework::transport {

class CustomReactor {

public:
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
    handlers_[typeid(T)] = lambda;
  }

  void react(IClient &client, IEvent &event) {
    handlers_[typeid(event)](client, event);
  }

private:
  std::unordered_map<std::type_index,
                     std::function<void(IClient &, const IEvent &)>>
          handlers_;
  DependencyInjector &dependency_injector_;
};

}// namespace openao::framework::transport
#endif// OPENAO_FRAMEWORK_TRANSPORT_CUSTOMREACTOR_H
