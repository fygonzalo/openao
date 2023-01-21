
#ifndef OPENAO_FRAMEWORK_TRANSPORT_CLIENT_H
#define OPENAO_FRAMEWORK_TRANSPORT_CLIENT_H

#include <asio/experimental/awaitable_operators.hpp>
#include <memory>

#include "customreactor.h"
#include "iclient.h"
#include "messagestream.h"

#include "serialization/deserializer.h"
#include "serialization/serializer.h"

using namespace asio::experimental::awaitable_operators;
using namespace openao::framework::serialization;

namespace openao::framework::transport {


class Client : public IClient {
public:
  Client(MessageStream stream, CustomReactor &reactor, Serializer &serializer,
         Deserializer &deserializer)
      : stream_(std::move(stream)), send_timer_(stream.get_executor()),
        reactor_(reactor), serializer_(serializer),
        deserializer_(deserializer) {
    send_timer_.expires_at(std::chrono::steady_clock::time_point::max());
  };

  void send(IEvent &event) override {
    BinaryBuffer buffer = serializer_.serialize(event);
    send_queue_.push_back(std::move(buffer));
    send_timer_.cancel_one();
  }

  void disconnect() override {
    connected_ = false;
    send_timer_.cancel_one();
  }

  awaitable<void> start() {
    co_await (receiver() && sender());
    stream_.close();
  }


  MessageStream &stream() { return stream_; }

private:
  awaitable<void> receiver() {
    // TODO: should process already received messages after disconenct?
    try {
      while (connected_) {
        try {
          auto buffer = co_await stream_.read();
          auto event = deserializer_.deserialize(buffer);
          reactor_.react(*this, *event);
        } catch (const char *message) {
          std::cout << std::string(message) << std::endl;
        }
      }
    } catch (std::exception &e) { disconnect(); }
  }

  awaitable<void> sender() {
    while (connected_) {
      std::error_code ec;
      co_await send_timer_.async_wait(asio::redirect_error(use_awaitable, ec));

      for (auto &b: send_queue_) { co_await stream_.send(b); }
      send_queue_.clear();
    }
  }

protected:
  MessageStream stream_;
  Serializer &serializer_;
  Deserializer &deserializer_;
  CustomReactor &reactor_;

  std::vector<BinaryBuffer> send_queue_;
  asio::steady_timer send_timer_;

  bool connected_ = true;
};

}// namespace openao::framework::transport

#endif// OPENAO_FRAMEWORK_TRANSPORT_CLIENT_H
