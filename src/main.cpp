#include "transport/server.h"

#include "login/login.h"
#include "repositories/impl/pqxx/account.h"
#include "repositories/impl/pqxx/character.h"
#include "services/account.h"

int main(int argc, char *argv[]) {
  pqxx::connection c("dbname=openao user=admin password=admin "
                     "hostaddr=127.0.0.1 port=5432");
  Repositories::PQXX::Account account{c};
  Repositories::PQXX::Character character{c};

  Services::Account as{account, character};
  LoginSystem ls{as};

  Server server(31000, ls);
  server.start();
}