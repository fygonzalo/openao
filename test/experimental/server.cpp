
#include <gtest/gtest.h>

#include "experimental/login/account/accountcontroller.h"
#include "experimental/login/account/authenticatecommand.h"
#include "experimental/transport/client.h"
#include "experimental/transport/server.h"

#include "mockclient.h"

using namespace openao::experimental::transport;
using namespace openao::experimental::serialization;
using namespace openao::experimental::login::account;


TEST(Server, test) {



  Serializer serializer;
  serializer.insert<CharacterListEvent>(0);

  Deserializer deserializer;
  deserializer.insert<AuthenticationCommand>(2);

  Injector injector;
  injector.create<BranchesService>();
  injector.create<AccountService>();

  io_context context;

  Server server(context, 30000, injector, serializer, deserializer);

  MockClient client;
  IClient &c = client;

  server.add_handler(AccountController::authenticate);

  MockClient mock_client;
  AuthenticationCommand command;

  auto l = [](IClient &c, AuthenticationCommand &a) {
    auto args = std::tuple(&c, a);
  };

  auto args = std::tuple(&client, &command);
  l(mock_client, command);

  server.recv(mock_client, command);

  // server.start();

  // context.run();
}