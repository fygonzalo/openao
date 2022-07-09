
#ifndef OPENAO_LOGIN_SYSTEM_H
#define OPENAO_LOGIN_SYSTEM_H

#include "transport/message.h"
#include <asio.hpp>

#include "login/messages/responses/redirect.h"
#include "messages/requests/auth.h"
#include "model/gameserver.h"
#include "services/account.h"

namespace Login {
class System  {
public:
  System(Services::Account &as) : as_(as){};

  awaitable<void> accept(MessageStream stream) {
    Message message = co_await stream.read();
    if (message.header.type != 0x02) stream.close();

    try {
      auto request = message.read<Messages::Requests::Auth>();
      co_await as_.authenticate(stream, request);

      Model::GameServer gm;
      gm.ip = "127.0.0.1";
      gm.port = 30001;

      Messages::Responses::Redirect gameserver;
      gameserver.session = 1;
      gameserver.server = gm;

      co_await stream.read();
      co_await stream.write(gameserver);
      co_await stream.read();
    } catch (std::exception & e) {
      std::cout << e.what() << std::endl;
      stream.close();
    }
  }

private:
  Services::Account &as_;
};
}// namespace Login

#endif// OPENAO_LOGIN_SYSTEM_H
