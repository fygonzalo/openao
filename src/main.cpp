#include "transport/server.h"

#include "login/services/account.h"
#include "login/system.h"
#include "game/system.h"

#include "repositories/impl/pqxx/account.h"
#include "repositories/impl/pqxx/character.h"


void launch_server(std::shared_ptr<Server> server)
{
  server->start();
}

int main(int argc, char *argv[]) {
  pqxx::connection c("dbname=openao user=admin password=admin "
                     "hostaddr=127.0.0.1 port=5432");
  Repositories::PQXX::Account account{c};
  Repositories::PQXX::Character character{c};

  Login::Services::Account as{account, character};
  Login::System ls{as};
  std::shared_ptr<Server> login_server{new Server(31000, ls)};
  std::cout << "Starting login server" << std::endl;
  std::thread t1(launch_server, login_server);

  Game::System gs{};
  std::shared_ptr<Server> game_server{new Server(31001, gs)};
  std::cout << "Starting game server" << std::endl;
  std::thread t2(launch_server, game_server);

  game_server->start();
  t1.join();
}