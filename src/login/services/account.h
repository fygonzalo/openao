
#ifndef OPENAO_SERVICES_ACCOUNT_H
#define OPENAO_SERVICES_ACCOUNT_H


#include "login/messages/requests/auth.h"
#include "login/messages/responses/charinfo.h"

#include "datasources/iaccount.h"
#include "datasources/icharacter.h"

#include "transport/messagestream.h"

namespace Login::Services {
class Account {
public:
  Account(Datasources::IAccount &iaccount,
          Datasources::ICharacter &icharacter)
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
    stream.write(charinfo);
  }

private:
  Datasources::IAccount &iaccount_;
  Datasources::ICharacter &icharacter_;
  // std::vector<Client>& players;
};
}// namespace Login::Services

#endif// OPENAO_SERVICES_ACCOUNT_H
