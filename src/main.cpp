#include "transport/server.h"

#include "repositories/impl/pqxx/character.h"
#include "repositories/impl/pqxx/account.h"

int main(int argc, char *argv[]) {
  pqxx::connection c("dbname=openao user=admin password=admin hostaddr=127.0.0.1 port=5432");
  Repositories::PQXX::Account account{c};
  Repositories::PQXX::Character character{c};

  Server server(31000, character, account);
  server.start();
}