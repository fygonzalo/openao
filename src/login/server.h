
#ifndef OPENAO_LOGIN_SERVER_H
#define OPENAO_LOGIN_SERVER_H

#include <asio.hpp>
#include <cstdint>
#include <memory>
#include <optional>
#include <unordered_set>

#include "datasources/impl/pqxx/account.h"
#include "datasources/impl/pqxx/character.h"
#include "datasources/impl/pqxx/inventory.h"
#include "login/handlers.h"
#include "login/services/account.h"
#include "pqxx/connection"
#include "transport/client.h"

namespace Login {

typedef std::function<void(Client &client, Message &message)> Handler;


class Server {

public:
  Server(uint16_t port, Handlers &handlers)
      : ctx(),
        acceptor(ctx, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)),
        handlers_(handlers) {
    loop_timer = std::make_shared<asio::steady_timer>(ctx);
    clients.reserve(30);
  }

  void start() {
    co_spawn(ctx, accept(), detached);
    co_spawn(ctx, update(), detached);
    ctx.run();
  }

private:
  awaitable<void> accept() {
    while (true) {
      MessageStream stream{
              ctx, CipherSet({0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00})};

      co_await acceptor.async_accept(stream.socket(), use_awaitable);
      co_await stream.init();

      clients.push_back(std::make_unique<Client>(std::move(stream)));
      clients.back()->start();
    }
  }

  awaitable<void> update() {
    while (true) {

      std::vector<int> disconnected;
      int i = 0;
      for (auto &c: clients) {

        if (!c->is_open()) {
          disconnected.push_back(i);
          continue;
        }

        std::optional<Message> m = c->read();
        if (m.has_value()) { handlers_[m->header.type](*c, *m); }
        i += 1;
      }

      std::reverse(disconnected.begin(), disconnected.end());


      for (auto i: disconnected) {
        Message message = Login::Messages::Requests::Disconnect();
        handlers_[Login::Messages::Requests::Disconnect::type](*clients[i], message);
        clients.erase(clients.begin() + i);
      }

      loop_timer->expires_after(std::chrono::seconds(1));
      co_await loop_timer->async_wait(use_awaitable);
    }
  }


  std::shared_ptr<asio::steady_timer> loop_timer;

  asio::io_context ctx;
  asio::ip::tcp::acceptor acceptor;

  std::vector<std::unique_ptr<Client>> clients;

  Handlers &handlers_;
};

}// namespace Login

#endif// OPENAO_LOGIN_SERVER_H
