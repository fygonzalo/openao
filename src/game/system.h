
#ifndef OPENAO_GAME_SYSTEM_H
#define OPENAO_GAME_SYSTEM_H

#include "game/controller/account.h"
#include "game/controller/items.h"
#include "game/messages/requests/auth.h"


namespace Game {
class System {
public:
  System(Controller::Account &account, Controller::Items &items)
      : account_(account), items_(items) {}

  awaitable<void> accept(MessageStream stream) {
    try {
      Message message = co_await stream.read();
      if (message.header.type != 0x02) stream.close();

      auto auth = message.read<Game::Messages::Requests::Auth>();
      co_await account_.preauth(stream, auth);

      for (;;) {
        message = co_await stream.read();
        if (message.header.type == 0x12) {
          auto mi = message.read<Game::Messages::Requests::MoveItem>();
          co_await items_.move_item(
                  stream, mi);
        }
      }
    } catch (std::exception &e) {
      std::cout << e.what() << std::endl;
      stream.close();
    }
  }

private:
  Controller::Account &account_;
  Controller::Items &items_;
};
}// namespace Game

#endif// OPENAO_GAME_SYSTEM_H
