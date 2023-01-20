
#include <sqlpp11/postgresql/connection.h>

#include "account/accountcontroller.h"
#include "account/repositories/impl/accountrepository.h"
#include "account/repositories/impl/characterrepository.h"

#include "serialization/serializer.h"
#include "transport/server.h"

using namespace openao;

using namespace openao::framework;
using namespace openao::framework::serialization;
using namespace openao::framework::transport;

using namespace openao::login::account;
using namespace login::account::repositories::impl;

int main(int argc, char *argv[]) {
  // INITIALIZE DATABASE CONNECTION
  io_context context;
  auto config = std::make_shared<sqlpp::postgresql::connection_config>();
  config->host = "database";
  config->password = "letmein";
  config->user = "openao";
  config->dbname = "openao";
  sqlpp::postgresql::connection db(config);

  // CONFIGURE SERVICES
  DependencyInjector dependency_injector;
  dependency_injector.create<IAccountRepository>(AccountRepository(db));
  dependency_injector.create<ICharacterRepository>(CharacterRepository(db));
  dependency_injector.create(BranchesService());

  // CONFIGURE COMMANDS
  CustomReactor reactor(dependency_injector);
  reactor.insert(AccountController::authenticate);
  reactor.insert(AccountController::enter_game);

  // CONFIGURE SERIALIZATION
  Serializer serializer;
  serializer.insert<CharacterListEvent>(0);
  serializer.insert<AuthErrorEvent>(0);
  serializer.insert<RedirectServerEvent>(4);
  serializer.insert<AnnouncementEvent>(12);

  // CONFIGURE DESERIALIZATION
  Deserializer deserializer;
  deserializer.insert<AuthenticationCommand>(2);
  deserializer.insert<EnterGameCommand>(6);

  // CONFIGURE SERVER
  transport::Server server(context, 30000, reactor, serializer, deserializer);
  server.start();

  // START LOOP
  asio::signal_set signals(context, SIGINT, SIGTERM);
  signals.async_wait([&](auto, auto) { context.stop(); });
  context.run();
}