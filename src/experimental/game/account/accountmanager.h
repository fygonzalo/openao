
#ifndef OPENAO_EXPERIMENTAL_GAME_ACCOUNTMANAGER_H
#define OPENAO_EXPERIMENTAL_GAME_ACCOUNTMANAGER_H

#include <unordered_map>
#include "experimental/iclient.h"

namespace openao::experimental::game {

class AccountManager {
public:
  uint32_t get_account_by_client(IClient& client) {
    return client_to_account[&client];
  }

  IClient* get(uint32_t account_id) {
    return account_to_client[account_id];
  }

  uint32_t get(IClient& client) {
    return client_to_account[&client];
  }

  void insert(IClient& client, uint32_t account_id) {
    client_to_account[&client] = account_id;
    account_to_client[account_id] = &client;
  }

  void remove(IClient &client) {
    auto account_id = get(client);
    account_to_client.erase(account_id);
    client_to_account.erase(&client);
  }

private:
  std::unordered_map<uint32_t, IClient*> account_to_client;
  std::unordered_map<IClient*, uint32_t> client_to_account;
};

}

#endif// OPENAO_EXPERIMENTAL_GAME_ACCOUNTMANAGER_H
