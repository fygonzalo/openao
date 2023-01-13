
#ifndef OPENAO_EXPERIMENTAL_TRANSPORT_CUSTOMREACTOR_H
#define OPENAO_EXPERIMENTAL_TRANSPORT_CUSTOMREACTOR_H
#include "experimental/di/injector.h"
#include "experimental/reactor.h"
#include "experimental/transport/iclient.h"

using namespace openao::experimental::di;

namespace openao::experimental::transport {

class CustomReactor {

public:
  CustomReactor(Injector& injector) : injector_(injector) {};

  template<typename T, typename... Services>
  void insert(void (*handler)(IClient &client, const T &t, Services...)) {
    auto lambda = [this, handler](IClient &client,
                                  const reactor::IEvent &event) {
      auto &cevent = static_cast<const T &>(event);
      auto args = std::make_tuple(std::ref(client), cevent,
                                  injector_.get<Services>()...);
      std::apply(handler, args);
    };
    handlers_[typeid(T)] = lambda;
  }

  void react(IClient& client, std::type_index index, reactor::IEvent &event) {
    handlers_[index](client, event);
  }

private:
  std::unordered_map<std::type_index,
                     std::function<void(IClient &, const reactor::IEvent &)>>
          handlers_;
  Injector &injector_;
};

}
#endif// OPENAO_EXPERIMENTAL_TRANSPORT_CUSTOMREACTOR_H
