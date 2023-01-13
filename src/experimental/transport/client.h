
#ifndef OPENAO_EXPERIMENTAL_TRANSPORT_CLIENT_H
#define OPENAO_EXPERIMENTAL_TRANSPORT_CLIENT_H

#include <memory>

#include "experimental/transport/customreactor.h"
#include "experimental/transport/iclient.h"
#include "experimental/transport/messagestream.h"

#include "experimental/reactor.h"
#include "experimental/serialization/deserializer.h"
#include "experimental/serialization/serializer.h"

using namespace openao::experimental::serialization;

namespace openao::experimental::transport {


class Client : public IClient {
public:
  Client(MessageStream stream, CustomReactor &reactor, Serializer &serializer,
         Deserializer &deserializer)
      : stream_(std::move(stream)), send_timer_(stream.get_executor()),
        reactor_(reactor), serializer_(serializer),
        deserializer_(deserializer) {
    send_timer_.expires_at(std::chrono::steady_clock::time_point::max());
  };

  void send(reactor::IEvent &event) override {
    BinaryBuffer buffer = serializer_.serialize(event.index(), event);
    send_queue_.push_back(std::move(buffer));
    send_timer_.cancel_one();
  }

  void start() {
    co_spawn(stream_.get_executor(), sender(), asio::detached);
    co_spawn(stream_.get_executor(), receiver(), asio::detached);
  }

  MessageStream &stream() { return stream_; }

private:
  awaitable<void> receiver() {
    while (true) {
      auto buffer = co_await stream_.read();
      auto [type, event] = deserializer_.deserialize(buffer);
      reactor_.react(*this, type, *event);
    }
  }

  awaitable<void> sender() {
    while (true) {
      std::error_code ec;
      co_await send_timer_.async_wait(asio::redirect_error(use_awaitable, ec));

      for (auto& b : send_queue_) {
        co_await stream_.send(b);
      }
    }
  }

protected:
  MessageStream stream_;
  Serializer &serializer_;
  Deserializer &deserializer_;
  CustomReactor &reactor_;

  std::vector<BinaryBuffer> send_queue_;
  asio::steady_timer send_timer_;
};

}// namespace openao::experimental::transport

#endif// OPENAO_EXPERIMENTAL_TRANSPORT_CLIENT_H
