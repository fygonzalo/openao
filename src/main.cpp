#include "transport/server.h"

#include "game/system.h"
#include "login/services/account.h"
#include "login/system.h"

#include "repositories/impl/pqxx/account.h"
#include "repositories/impl/pqxx/character.h"

int main(int argc, char *argv[]) {
  pqxx::connection c("dbname=openao user=admin password=admin "
                     "hostaddr=127.0.0.1 port=5432");
  Repositories::PQXX::Account account{c};
  Repositories::PQXX::Character character{c};

  Login::Services::Account as{account, character};
  Login::System login{as};
  std::thread t1([&login]() { Server{30000, login}.start(); });

  Game::Services::Account gsa{character};
  Game::System game{gsa};
  std::thread t2([&game]() { Server{30001, game}.start(); });

  t1.join();
  t2.join();
}