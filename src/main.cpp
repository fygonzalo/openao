#include "transport/server.h"

#include "login/services/account.h"

#include "datasources/impl/pqxx/account.h"
#include "datasources/impl/pqxx/character.h"
#include "game/server.h"
#include "login/server.h"

int main(int argc, char *argv[]) {
  pqxx::connection conn("dbname=openao user=admin password=admin "
                        "hostaddr=127.0.0.1 port=5432");
  Datasources::PQXX::Account account(conn);
  Datasources::PQXX::Character character(conn);

  Login::Services::Account account_service(account, character);

  Login::Handlers handlers;
  handlers.add<Login::Messages::Requests::Auth>(
          [&account_service](auto &&c, auto &&m) {
            account_service.authenticate(c, m);
          });
  handlers.add<Login::Messages::Requests::SetPin>(
          [&account_service](auto &&c, auto &&m) {
            account_service.set_pin(c, m);
          });
  handlers.add<Login::Messages::Requests::Disconnect>(
          [&account_service](auto &&c, auto &&m) {
            account_service.disconnect(c, m);
          });

  handlers.add<Login::Messages::Requests::EnterGame>(
          [&account_service](auto &&c, auto &&m) {
            account_service.enter_game(c, m);
          });

  Login::Server login{30000, handlers};
  std::thread t1([&login]() { login.start(); });


  Game::Server game{30001, conn};
  std::thread t2([&game]() { game.start(); });

  t1.join();
  t2.join();
}