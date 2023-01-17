#include "transport/server.h"

#include "account/accountcontroller.h"
#include "serialization/serializer.h"
#include "transport/server.h"

using namespace openao;
using namespace openao::framework::serialization;
using namespace openao::login::account;
using namespace openao::framework;

int main(int argc, char *argv[]) {
  io_context context;

  DependencyInjector dependency_injector;
  dependency_injector.create<BranchesService>();
  dependency_injector.create<AccountService>();

  CustomReactor reactor(dependency_injector);
  reactor.insert(AccountController::authenticate);

  Serializer serializer;
  serializer.insert<CharacterListEvent>(0);

  Deserializer deserializer;
  deserializer.insert<AuthenticationCommand>(2);

  transport::Server server(context, 30000, reactor, serializer, deserializer);
  server.start();

  asio::signal_set signals(context, SIGINT, SIGTERM);
  signals.async_wait([&](auto, auto) { context.stop(); });
  context.run();
}