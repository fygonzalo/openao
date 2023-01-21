#include "transport/server.h"

#include "character/charactercontroller.h"
#include "character/charactermanager.h"
#include "character/repositories/impl/characterrepository.h"

#include "inventory/inventorycontroller.h"
#include "inventory/repositories/impl/inventoryrepository.h"

using namespace openao::framework::di;
using namespace openao::framework::serialization;
using namespace openao::framework::transport;


using namespace openao::game::inventory;
using namespace openao::game::inventory::commands;
using namespace openao::game::inventory::repositories::impl;

using namespace openao::game::character;
using namespace openao::game::character::commands;
using namespace openao::game::character::events;
using namespace openao::game::character::repositories::impl;

int main(int argc, char *argv[]) {
  // INITIALIZE DATABASE CONNECTION
  auto config = std::make_shared<sqlpp::postgresql::connection_config>();
  config->host = "localhost";
  config->password = "letmein";
  config->user = "openao";
  config->dbname = "openao";
  sqlpp::postgresql::connection db(config);


  io_context context;

  DependencyInjector dependency_injector;
  dependency_injector.create<ICharacterRepository>(CharacterRepository(db));
  dependency_injector.create(CharacterManager());
  dependency_injector.create<IInventoryRepository>(InventoryRepository(db));

  CustomReactor reactor(dependency_injector);
  reactor.insert(CharacterController::authenticate);
  reactor.insert(CharacterController::interact);
  reactor.insert(InventoryController::load_inventory);

  Deserializer deserializer;
  deserializer.insert<AuthenticateCommand>(2);
  deserializer.insert<LoadInventoryCommand>(3);
  deserializer.insert<Interact>(22);

  Serializer serializer;
  serializer.insert<CharacterDetailEvent>(2);
  serializer.insert<ShowEmote>(25);
  serializer.insert<LoadInventoryEvent>(26);
  serializer.insert<LoadFunctionBarEvent>(91);


  // CONFIGURE SERVER
  Server server(context, 30001, reactor, serializer, deserializer);
  server.start();

  // START LOOP
  asio::signal_set signals(context, SIGINT, SIGTERM);
  signals.async_wait([&](auto, auto) { context.stop(); });
  context.run();
}
