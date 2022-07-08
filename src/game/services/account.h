
#ifndef OPENAO_GAME_SERVICES_ACCOUNT_H
#define OPENAO_GAME_SERVICES_ACCOUNT_H

#include "game/messages/requests/auth.h"

#include "transport/messagestream.h"

#include "repositories/icharacter.h"


namespace Game::Services{

class Account {
public:
  Account(Repositories::ICharacter& icharacter) : icharacter_(icharacter) {}

  void authenticate(MessageStream& stream, Messages::Requests::Auth& request) {

  }

private:
  Repositories::ICharacter& icharacter_;

};

}

#endif// OPENAO_GAME_SERVICES_ACCOUNT_H
