
#ifndef OPENAO_GAME_SYSTEM_H
#define OPENAO_GAME_SYSTEM_H

#include "game/messages/requests/auth.h"


namespace Game {
class System {
public:
  awaitable<void> accept(MessageStream stream) {
    Message message = co_await stream.read();
    if (message.header.type != 0x02)
      stream.close();

    auto auth = message.read<Game::Messages::Requests::Auth>();
    if (auth.session != 1)
      stream.close();

    for (;;)
      co_await stream.read();

  }
};
}

#endif// OPENAO_GAME_SYSTEM_H
