
#include <gtest/gtest.h>

#include "experimental/transport/server.h"
#include "experimental/transport/client.h"
#include "experimental/login/account/authenticatecommand.h"
#include "experimental/login/account/accountcontroller.h"

#include "mockclient.h"

using namespace openao::experimental::transport;
using namespace openao::experimental::serialization;
using namespace openao::experimental::login::account;

TEST(Server, test) {

  BranchesService * pbs = new BranchesService();
  Injectable * pi = pbs;
  BranchesService * s = (BranchesService*)pi;

  Serializer serializer;
  serializer.insert<CharacterListEvent>(0);

  Deserializer deserializer;
  deserializer.insert<AuthenticationCommand>(2);

  BranchesService branches_service;
  AccountService account_service;

  Injector injector;
  injector.insert(branches_service);
  injector.insert(account_service);

  io_context context;

  Server server(context, 30000, injector, serializer, deserializer);
  server.add_handler(AccountController::authenticate);

  MockClient mock_client;
  AuthenticationCommand command;
  server.recv(mock_client, command);

  server.start();

  context.run();
}