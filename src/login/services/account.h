
#ifndef OPENAO_SERVICES_ACCOUNT_H
#define OPENAO_SERVICES_ACCOUNT_H


#include "login/messages/requests/auth.h"
#include "login/messages/responses/charinfo.h"

#include "repositories/iaccount.h"
#include "repositories/icharacter.h"

#include "transport/messagestream.h"

namespace Login::Services {
class Account {
public:
  Account(Repositories::IAccount &iaccount,
          Repositories::ICharacter &icharacter)
      : iaccount_(iaccount), icharacter_(icharacter){};

  awaitable<void> authenticate(MessageStream &stream,
                               Login::Messages::Requests::Auth &request) {
    auto account = iaccount_.find_account_by_username_password(
            request.username, request.password);

    if (!account) co_return;

    // Genreate entity id
    // Cast spawn entity event

    auto characters = icharacter_.get_characters_by_account(account->id);
    auto branches = Model::Branches({10});
    Messages::Responses::CharInfo charinfo(account.value(), characters,
                                           branches);
    co_await stream.write(charinfo);
  }

private:
  Repositories::IAccount &iaccount_;
  Repositories::ICharacter &icharacter_;
  // std::vector<Client>& players;
};
}// namespace Login::Services

#endif// OPENAO_SERVICES_ACCOUNT_H
