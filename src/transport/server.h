
#ifndef OPENAO_SERVER_H
#define OPENAO_SERVER_H

#include <iostream>
#include <memory>
#include <vector>

#include <boost/asio.hpp>

#include "transport/client.h"

#include "repositories/iaccount.h"
#include "repositories/icharacter.h"

using boost::asio::awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::io_context;
using boost::asio::use_awaitable;
using boost::asio::ip::tcp;


class Server {

public:
  Server(uint16_t port, Repositories::ICharacter &icharacter, Repositories::IAccount &iaccount)
      : ctx_(), acceptor_(ctx_, tcp::endpoint(tcp::v4(), port)),
        icharacter_(icharacter),
        iaccount_(iaccount){

        };

  void start() {
    co_spawn(ctx_, listen(), detached);
    ctx_.run();
  };

  awaitable<void> listen() {
    for (;;) {
      auto &client = clients.emplace_back(new Client(ctx_, icharacter_, iaccount_));
      co_await acceptor_.async_accept(client->socket(), use_awaitable);

      co_spawn(ctx_, accept(client.get()), detached);
    }
  }

  awaitable<void> accept(Client *client) { co_await client->start(); }

private:
  std::vector<std::unique_ptr<Client>> clients;

  io_context ctx_;
  tcp::acceptor acceptor_;

  Repositories::ICharacter &icharacter_;
  Repositories::IAccount &iaccount_;
};


#endif// OPENAO_SERVER_H
