
#ifndef OPENAO_GAME_SYSTEM_H
#define OPENAO_GAME_SYSTEM_H

#include "game/controller/account.h"
#include "game/controller/actions.h"
#include "game/controller/chat.h"
#include "game/controller/items.h"
#include "game/controller/movement.h"
#include "game/messages/requests/auth.h"
#include "game/messages/requests/logout_1.h"
#include "game/messages/requests/postauth.h"


namespace Game {
class System {
public:
  System(Controller::Account &account, Controller::Items &items,
         Controller::Actions &actions, Controller::Movement &movement, Controller::Chat &chat)
      : account_(account), items_(items), actions_(actions),
        movement_(movement), chat_(chat) {}

  awaitable<void> accept(MessageStream stream) {
    try {
      Message message = co_await stream.read();
      if (message.header.type != 0x02) stream.close();

      auto auth = message.read<Game::Messages::Requests::Auth>();
      co_await account_.preauth(stream, auth);

      message = co_await stream.read();
      auto postauth = message.read<Game::Messages::Requests::PostAuth>();
      co_await account_.postauth(stream, postauth);

      for (;;) {
        message = co_await stream.read();
        if (message.header.type == 0x12) {
          auto mi = message.read<Game::Messages::Requests::MoveItem>();
          co_await items_.move_item(stream, mi);
        } else if (message.header.type == 22) {
          auto mi = message.read<Game::Messages::Requests::Interact>();
          co_await actions_.execute(stream, mi);
        } else if (message.header.type == 4) {
          auto mi = message.read<Game::Messages::Requests::Move>();
          co_await movement_.move(stream, mi);
        } else if (message.header.type == Game::Messages::Requests::Logout1::type) {
          auto mi = message.read<Game::Messages::Requests::Logout1>();
          co_await account_.logout(stream, mi);
        } else if (message.header.type == Game::Messages::Requests::GlobalMessage::type) {
          auto mi = message.read<Game::Messages::Requests::GlobalMessage>();
          co_await chat_.global_message(stream, mi);
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
  Controller::Actions &actions_;
  Controller::Movement &movement_;
  Controller::Chat &chat_;
};
}// namespace Game

#endif// OPENAO_GAME_SYSTEM_H
