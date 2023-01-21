
#ifndef OPENAO_FRAMEWORK_TRANSPORT_SERVER_H
#define OPENAO_FRAMEWORK_TRANSPORT_SERVER_H

#include "asio.hpp"

#include <functional>

#include "client.h"
#include "customreactor.h"
#include "messagestream.h"

#include "serialization/deserializer.h"
#include "serialization/serializer.h"

using asio::io_context;
using namespace openao::framework::serialization;


namespace openao::framework::transport {


using asio::awaitable;
using asio::ip::tcp;

class Server {
public:
  Server(io_context &context, uint16_t port, CustomReactor &reactor,
         Serializer &serializer, Deserializer &deserializer)
      : context_(context), reactor_(reactor), serializer_(serializer),
        deserializer_(deserializer),
        acceptor_(context_, tcp::endpoint(tcp::v4(), port)){};

  void start() { co_spawn(context_.get_executor(), listener(), detached); }

private:
  awaitable<void> listener() {
    while (true) {
      auto stream = MessageStream(
              context_,
              CipherSet{{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}});
      co_await acceptor_.async_accept(stream.socket(), use_awaitable);
      co_await stream.init();

      auto client = std::make_unique<Client>(std::move(stream), reactor_,
                                             serializer_, deserializer_);
      auto [it, ok] = clients_.emplace(std::move(client));
      if (ok) co_spawn(context_, worker(it), detached);
    }
  }

  awaitable<void> worker(auto it) {
    co_await it->get()->start();
    clients_.erase(it);
  }

private:
  Serializer &serializer_;
  Deserializer &deserializer_;
  CustomReactor &reactor_;

  std::unordered_set<std::unique_ptr<Client>> clients_;

  io_context &context_;
  tcp::acceptor acceptor_;
};

}// namespace openao::framework::transport

#endif// OPENAO_FRAMEWORK_TRANSPORT_SERVER_H
