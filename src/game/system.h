
#ifndef OPENAO_GAME_SYSTEM_H
#define OPENAO_GAME_SYSTEM_H

#include "game/messages/requests/auth.h"
#include "transport/system.h"


namespace Game {
class System : public ::System {
public:
  awaitable<void> handle(MessageStream stream) override {
    std::cout << "Player joined game server" << std::endl;
    Message message = co_await stream.read();
    if (message.header.type != 0x02)
      stream.close();

    auto auth = message.read<Auth>();
    if (auth.session != 1)
      stream.close();

    for (;;)
      co_await stream.read();

  }
};
}

#endif// OPENAO_GAME_SYSTEM_H
