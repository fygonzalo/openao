
#ifndef OPENAO_EXPERIMENTAL_TRANSPORT_SERVER_H
#define OPENAO_EXPERIMENTAL_TRANSPORT_SERVER_H

#include <asio.hpp>

#include <functional>

#include "experimental/transport/client.h"
#include "experimental/transport/customreactor.h"
#include "experimental/transport/messagestream.h"

#include "experimental/serialization/deserializer.h"
#include "experimental/serialization/serializer.h"

using asio::io_context;
using namespace openao::experimental::serialization;


namespace openao::experimental::transport {


using asio::awaitable;
using asio::ip::tcp;

class Server {
public:
  Server(io_context &context, uint16_t port, CustomReactor &reactor,
         Serializer &serializer, Deserializer &deserializer)
      : context_(context), reactor_(reactor), serializer_(serializer),
        deserializer_(deserializer),
        acceptor_(context_, tcp::endpoint(tcp::v4(), port)){};

  void start() {
    co_spawn(context_.get_executor(), listen(), detached);
  }

private:
  awaitable<void> listen() {
    while (true) {
      auto stream = MessageStream(
              context_,
              CipherSet{{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}});
      co_await acceptor_.async_accept(stream.socket(), use_awaitable);
      co_await stream.init();

      auto client = std::make_unique<Client>(std::move(stream), reactor_,
                                             serializer_, deserializer_);
      auto [el, ok] = clients_.emplace(std::move(client));
      if (ok) el->get()->start();
    }
  }

private:
  Serializer &serializer_;
  Deserializer &deserializer_;
  CustomReactor &reactor_;

  io_context &context_;
  tcp::acceptor acceptor_;

  std::unordered_set<std::unique_ptr<Client>> clients_;
};

}// namespace openao::experimental::transport

#endif// OPENAO_EXPERIMENTAL_TRANSPORT_SERVER_H