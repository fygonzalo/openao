
#ifndef OPENAO_TRANSPORT_CLIENT_H
#define OPENAO_TRANSPORT_CLIENT_H

#include <asio.hpp>
#include <chrono>
#include <deque>

#include "messagestream.h"

/**
 * Provides a safe concurrent interface to comunicate with clients.
 */
class Client {

public:
  Client(MessageStream stream)
      : stream_(std::move(stream)), send_timer_(stream.get_executor()) {
    send_timer_.expires_at(std::chrono::steady_clock::time_point::max());
  };

  void start() {
    co_spawn(stream_.get_executor(), writer(), asio::detached);
    co_spawn(stream_.get_executor(), reader(), asio::detached);
  }

  void write(Message message) {
    send_queue_.push_back(message);
    send_timer_.cancel_one();
  }

  void close() { stream_.close(); }

  bool is_open() {
    try {
      return stream_.socket().is_open();
    } catch (std::exception &e) { return false; }
  }

  std::optional<Message> read() {
    if (recv_queue_.empty()) return {};

    Message m = recv_queue_.front();
    recv_queue_.pop_front();
    return m;
  }

  friend bool operator== (const Client& c1, const Client& c2)
  {
    return &c1.stream_.socket() == &c2.stream_.socket();
  }


protected:
  awaitable<void> reader() {
    try {
      while (true) {
        Message message = co_await stream_.read();
        recv_queue_.push_back(message);
      }
    } catch (std::exception &e) {
      // Must terminate the connection
      close();
    }
  }

  awaitable<void> writer() {
    while (true) {

      std::error_code ec;
      co_await send_timer_.async_wait(redirect_error(use_awaitable, ec));

      while (!send_queue_.empty()) {
        co_await stream_.write(send_queue_.front());
        send_queue_.pop_front();
      }
    }
  }

private:
  MessageStream stream_;

  asio::steady_timer send_timer_;
  std::deque<Message> send_queue_;

  std::deque<Message> recv_queue_;
};

#endif// OPENAO_TRANSPORT_CLIENT_H
