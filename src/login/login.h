
#ifndef OPENAO_LOGIN_H
#define OPENAO_LOGIN_H

#include "transport/message.h"
#include "transport/system.h"
#include <asio.hpp>

#include "messages/requests/auth.h"
#include "messages/responses/redirect.h"
#include "model/gameserver.h"
#include "services/account.h"


class LoginSystem : public System {
public:
  LoginSystem(Services::Account &as) : as_(as){};

  awaitable<void> handle(MessageStream stream) override {
    Message message = co_await stream.read();
    if (message.header.type != 0x02) stream.close();

    auto request = message.read<Messages::Requests::Auth>();
    co_await as_.authenticate(stream, request);

    Model::GameServer gm;
    gm.ip = "127.0.0.1";
    gm.port = 31002;

    Messages::Responses::Redirect gameserver;
    gameserver.session = 1231231;
    gameserver.server = gm;

    co_await stream.read();
    co_await stream.write(gameserver);
    co_await stream.read();
  }

private:
  Services::Account &as_;
};

#endif// OPENAO_LOGIN_H
