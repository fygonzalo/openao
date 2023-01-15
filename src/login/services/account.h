
#ifndef OPENAO_SERVICES_ACCOUNT_H
#define OPENAO_SERVICES_ACCOUNT_H


#include "login/messages/requests/auth.h"
#include "login/messages/requests/create_char.h"
#include "login/messages/responses/charinfo.h"
#include <map>

#include "datasources/iaccount.h"
#include "datasources/icharacter.h"

#include "login/messages/requests/change_pin.h"
#include "login/messages/requests/delete_pin.h"
#include "login/messages/requests/disconnect.h"
#include "login/messages/requests/enter_game.h"
#include "login/messages/requests/set_pin.h"
#include "login/messages/responses/announcement.h"
#include "login/messages/responses/change_pin.h"
#include "login/messages/responses/delete_pin.h"
#include "login/messages/responses/redirect.h"
#include "login/messages/responses/set_pin.h"
#include "transport/client.h"
#include "transport/messagestream.h"


namespace Login::Services {

struct Player {
  uint32_t id;
  Client &client;

  Player(uint32_t id, Client &client) : id(id), client(client){};
};

class PlayerList {
public:
  PlayerList() { players.reserve(30); }

  void create(uint32_t id, Client &client) {
    players.push_back(std::make_unique<Player>(id, client));
  }

  void remove(Player &player) {
    for (int i = 0; i < players.size(); i++) {
      if (players.at(i).get() == &player) {
        players.erase(players.begin() + i);
        break;
      }
    }
  }

  Player *find_by_client(Client &client) {
    for (auto &p: players) {
      if (p->client == client) return p.get();
    }
    return nullptr;
  }

  Player *find_by_id(uint32_t id) {
    for (auto &p: players) {
      if (p->id == id) { return p.get(); }
    }
    return nullptr;
  }

private:
  std::vector<std::unique_ptr<Player>> players;
};

class Account {
public:
  Account(Datasources::IAccount &iaccount, Datasources::ICharacter &icharacter)
      : iaccount_(iaccount), icharacter_(icharacter){};

  void authenticate(Client &client, const Messages::Requests::Auth &request) {
    auto account = iaccount_.find_account_by_username_password(
            request.username, request.password);

    if (!account) {
      client.write(Messages::Responses::AuthError{.code = 0x98});
      client.disconnect();
      return;
    };

    if (auto player = players.find_by_id(account->id)) {
      player->client.disconnect();
      client.disconnect();
      return;
    } else {
      players.create(account->id, client);
    }

    auto characters = icharacter_.get_characters_by_account(account->id);
    auto branches = Model::Branches({10});
    Messages::Responses::CharInfo charinfo(account.value(), characters,
                                           branches);
    client.write(charinfo);
  }

  void disconnect(Client &client, const Login::Messages::Requests::Disconnect &request) {
    if (auto player = players.find_by_client(client)) {
      player->client.disconnect();
      players.remove(*player);
    }
  }

  void set_pin(Client &client,
               const Login::Messages::Requests::SetPin &request) {
    auto player = players.find_by_client(client);
    if (!player) return;

    auto status = iaccount_.set_pin(player->id, request.password, request.pin);
    if (status) {
      Messages::Responses::SetPin result{.status = true};
      player->client.write(result);
    } else {
      Messages::Responses::SetPin result{.status = false};
      player->client.write(result);
    }

  }

  void enter_game(Client &client, const Login::Messages::Requests::EnterGame &request) {
    Model::GameServer gm;
    gm.ip = "127.0.0.1";
    gm.port = 30001;

    Messages::Responses::Redirect rd;
    rd.session = 1;
    rd.server = gm;

    client.write(rd);

    disconnect(client, Login::Messages::Requests::Disconnect());
  }


private:
  Datasources::IAccount &iaccount_;
  Datasources::ICharacter &icharacter_;

  PlayerList players;
};
}// namespace Login::Services

#endif// OPENAO_SERVICES_ACCOUNT_H
