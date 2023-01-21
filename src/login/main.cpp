
#include <sqlpp11/postgresql/connection.h>

#include "account/controller.h"
#include "account/repository.h"

#include "character/repository.h"

#include "serialization/serializer.h"
#include "transport/server.h"

using namespace openao;

using namespace openao::framework;
using namespace openao::framework::serialization;
using namespace openao::framework::transport;

using namespace openao::login;

using namespace login::account;


int main(int argc, char *argv[]) {
  // INITIALIZE DATABASE CONNECTION
  io_context context;
  auto config = std::make_shared<sqlpp::postgresql::connection_config>();
  config->host = "localhost";
  config->password = "letmein";
  config->user = "openao";
  config->dbname = "openao";
  sqlpp::postgresql::connection db(config);

  // CONFIGURE SERVICES
  DependencyInjector dependency_injector;
  dependency_injector.create<account::IRepository>(account::Repository(db));
  dependency_injector.create<character::IRepository>(character::Repository(db));
  dependency_injector.create(BranchesService());

  // CONFIGURE COMMANDS
  CustomReactor reactor(dependency_injector);
  reactor.insert(account::Controller::authenticate);
  reactor.insert(account::Controller::enter_game);

  // CONFIGURE SERIALIZATION
  Serializer serializer;
  serializer.insert<account::events::CharacterList>(0);
  serializer.insert<account::events::AuthError>(0);
  serializer.insert<account::events::RedirectServer>(4);
  serializer.insert<account::events::Announcement>(12);

  // CONFIGURE DESERIALIZATION
  Deserializer deserializer;
  deserializer.insert<account::commands::Authenticate>(2);
  deserializer.insert<account::commands::EnterGame>(6);

  // CONFIGURE SERVER
  transport::Server server(context, 30000, reactor, serializer, deserializer);
  server.start();

  // START LOOP
  asio::signal_set signals(context, SIGINT, SIGTERM);
  signals.async_wait([&](auto, auto) { context.stop(); });
  context.run();
}