#include <asio.hpp>
#include <sqlpp11/postgresql/connection.h>

#include "di/dependency_injector.h"

#include "transport/server.h"

#include "character/charactercontroller.h"

using namespace openao::framework::di;
using namespace openao::framework::serialization;
using namespace openao::framework::transport;

using namespace openao::game::character;
using namespace openao::game::character::commands;
using namespace openao::game::character::events;


int main(int argc, char *argv[]) {

  io_context context;

  DependencyInjector dependency_injector;

  CustomReactor reactor(dependency_injector);
  reactor.insert(CharacterController::authenticate);

  Deserializer deserializer;
  deserializer.insert<AuthenticateCommand>(2);

  Serializer serializer;
  serializer.insert<CharacterDetailEvent>(2);


  // CONFIGURE SERVER
  Server server(context, 30001, reactor, serializer, deserializer);
  server.start();

  // START LOOP
  asio::signal_set signals(context, SIGINT, SIGTERM);
  signals.async_wait([&](auto, auto) { context.stop(); });
  context.run();
}