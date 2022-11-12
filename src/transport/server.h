
#ifndef OPENAO_SERVER_H
#define OPENAO_SERVER_H

#include <iostream>
#include <memory>
#include <vector>

#include <asio.hpp>


#include "transport/messagestream.h"

#include "datasources/iaccount.h"
#include "datasources/icharacter.h"

using asio::awaitable;
using asio::co_spawn;
using asio::detached;
using asio::io_context;
using asio::use_awaitable;
using asio::ip::tcp;


template <typename System>
class Server {

public:
  Server(uint16_t port, System &system)
      : ctx_(), acceptor_(ctx_, tcp::endpoint(tcp::v4(), port)),
        system_(system){}

  void start() {
    co_spawn(ctx_, listen(), detached);
    ctx_.run();
  }

  awaitable<void> listen() {
    for (;;) {
      MessageStream stream{ctx_, CipherSet({0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                            0x00, 0x00, 0x00, 0x00})};
      co_await acceptor_.async_accept(stream.socket(), use_awaitable);
      stream.init();
      co_spawn(ctx_, system_.accept(std::move(stream)), detached);
    }
  }

private:
  io_context ctx_;
  tcp::acceptor acceptor_;

  System &system_;
};


#endif// OPENAO_SERVER_H
