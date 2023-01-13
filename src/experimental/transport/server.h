
#ifndef OPENAO_EXPERIMENTAL_TRANSPORT_SERVER_H
#define OPENAO_EXPERIMENTAL_TRANSPORT_SERVER_H

#include <asio.hpp>

#include <functional>

#include "experimental/transport/client.h"
#include "experimental/transport/iclient.h"

#include "experimental/di/injector.h"
#include "experimental/reactor.h"
#include "experimental/serialization/deserializer.h"
#include "experimental/serialization/serializer.h"

using asio::io_context;
using namespace openao::experimental::serialization;
using namespace openao::experimental::di;

namespace openao::experimental::transport {



class Server {
public:
  Server(io_context &context, uint16_t port, Injector &injector,
         Serializer &serializer, Deserializer &deserializer)
      : context_(context), injector_(injector), serializer_(serializer),
        deserializer_(deserializer){};


  template<typename T, typename... Services>
  void add_handler(void (*handler)(IClient &client, const T &t, Services...)) {
    auto lambda = [this, handler](IClient &client,
                                  const reactor::IEvent &event) {
      auto &cevent = static_cast<const T &>(event);
      std::tuple args =
              std::make_tuple(std::ref(client), cevent,
                              injector_.get<Services>()...);
      std::apply(handler, args);
    };
    handlers_[typeid(T)] = lambda;
  }


  template<typename T>
  void recv(IClient &client, const T &t) {
    handlers_[typeid(T)](client, t);
  }

  void start() {}

private:
  Serializer &serializer_;
  Deserializer &deserializer_;
  Injector &injector_;

  std::unordered_map<std::type_index,
                     std::function<void(IClient &, const reactor::IEvent &)>>
          handlers_;

  io_context &context_;
};

}// namespace openao::experimental::transport

#endif// OPENAO_EXPERIMENTAL_TRANSPORT_SERVER_H
