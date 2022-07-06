
#ifndef OPENAO_CLIENT_H
#define OPENAO_CLIENT_H

#include "login/authrequest.h"
#include "login/authresponse.h"
#include "transport/messagestream.h"

#include "model/branches.h"
#include "repositories/iaccount.h"
#include "repositories/icharacter.h"

#include "messages/responses/charinfo.h"

class Client {
public:
  Client(io_context &ctx, Repositories::ICharacter &character_repository, Repositories::IAccount& iaccount)
      : stream_(ctx,
                CipherSet({0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                           0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00})),
        character_repository_(character_repository),
        iaccount_(iaccount) {};

  tcp::socket &socket() { return stream_.socket(); }

  awaitable<void> start() {
    co_await stream_.init();

    Message message = co_await stream_.read();
    if (message.header.type != 0x02) {
      stop();
      co_return;
    }

    auto request = message.read<AuthRequest>();
    auto account = iaccount_.find_account_by_username_password(
            request.username.c_str(), request.password.c_str());

    if (!account) {
      InvalidAuthResponse response;
      response.code = AuthStatus::INVALID_USERNAME_PASSWORD;
      co_await stream_.write(response);
      stop();
      co_return;
    }

    auto characters = character_repository_.get_characters_by_account(account->id);
    auto branches = Model::Branches({10});

    Messages::Responses::CharInfo charinfo(account.value(), characters, branches);
    co_await stream_.write(charinfo);

    // Await client action
    auto action = co_await stream_.read();
  }


  awaitable<void> stop() {
    stream_.close();
    co_return;
  };

private:
  MessageStream stream_;

  Repositories::ICharacter &character_repository_;
  Repositories::IAccount &iaccount_;
};

#endif// OPENAO_CLIENT_H
