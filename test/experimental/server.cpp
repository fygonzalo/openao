
#include <gtest/gtest.h>

#include "experimental/login/account/accountcontroller.h"
#include "experimental/login/account/authenticatecommand.h"
#include "experimental/transport/client.h"
#include "experimental/transport/server.h"

using namespace openao::experimental::transport;
using namespace openao::experimental::serialization;
using namespace openao::experimental::login::account;
using namespace openao::experimental::reactor;



TEST(Server, test) {

  io_context context;

  Injector injector;
  injector.create<BranchesService>();
  injector.create<AccountService>();

  CustomReactor reactor(injector);
  reactor.insert(AccountController::authenticate);

  Serializer serializer;
  serializer.insert<CharacterListEvent>(0);

  Deserializer deserializer;
  deserializer.insert<AuthenticationCommand>(2);

  Server server(context, 30000, reactor, serializer, deserializer);
  server.start();

  context.run();
}