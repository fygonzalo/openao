
#ifndef OPENAO_GAME_SYSTEM_H
#define OPENAO_GAME_SYSTEM_H

#include "game/messages/requests/auth.h"
#include "game/services/account.h"


namespace Game {
class System {
public:
  System(Services::Account& account) : account_(account) {}

  awaitable<void> accept(MessageStream stream) {
    try {
      Message message = co_await stream.read();
      if (message.header.type != 0x02) stream.close();

      auto auth = message.read<Game::Messages::Requests::Auth>();
      co_await account_.authenticate(stream, auth);

      for (;;) co_await stream.read();
    } catch (std::exception& e) {
      std::cout << e.what() << std::endl;
      stream.close();
    }

  }

private:
  Services::Account& account_;
};
}

#endif// OPENAO_GAME_SYSTEM_H
