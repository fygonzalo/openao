
#ifndef OPENAO_GAME_SERVER_H
#define OPENAO_GAME_SERVER_H

#include <asio.hpp>
#include <cstdint>
#include <unordered_set>

#include "player.h"
#include "playermanager.h"
#include "transport/client.h"
#include "transport/messagestream.h"

namespace Game {

using namespace asio::ip;
using asio::awaitable;

class Server {
public:
  Server(uint16_t port, pqxx::connection &conn)
      : ctx(), acceptor_(ctx, tcp::endpoint(tcp::v4(), port)),
        update_timer_(ctx), conn_(conn) {}

  void start() {
    co_spawn(ctx.get_executor(), listen(), asio::detached);
    ctx.run();
  }

protected:
  awaitable<void> listen() {
    while (true) {
      MessageStream stream(
              ctx, CipherSet({0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
      co_await acceptor_.async_accept(stream.socket(), use_awaitable);
      co_await stream.init();
      auto it = clients.emplace(
              std::make_unique<Player>(std::move(stream), conn_, em_, pm_));
      if (it.second) {
        std::cout << "Client connected!" << std::endl;
        it.first->get()->start();
      }
    }
  }

private:
  asio::io_context ctx;

  tcp::acceptor acceptor_;

  std::unordered_set<std::unique_ptr<Player>> clients;
  pqxx::connection& conn_;

  asio::steady_timer update_timer_;
  EntityManager em_;
  PlayerManager pm_;
};

}// namespace Game

#endif// OPENAO_GAME_SERVER_H
