#include "transport/server.h"

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
  Login::System ls{as};

  Server server(31000, ls);
  server.start();
}