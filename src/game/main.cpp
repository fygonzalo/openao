#include "transport/server.h"

#include "character/controller.h"
#include "character/manager.h"
#include "character/repository.h"

#include "inventory/controller.h"
#include "inventory/manager.h"
#include "inventory/repository.h"

#include "chat/controller.h"
#include "entity/manager.h"
#include "movement/controller.h"
#include "stage/manager.h"

using namespace openao::framework::di;
using namespace openao::framework::serialization;
using namespace openao::framework::transport;


using namespace openao::game::inventory;
using namespace openao::game::character;

using namespace openao::game;

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
  dependency_injector.create<character::IRepository>(character::Repository(db));
  dependency_injector.create(character::Manager());
  dependency_injector.create<inventory::IRepository>(inventory::Repository(db));
  dependency_injector.create(stage::Manager());
  dependency_injector.create(entity::Manager());
  dependency_injector.create(inventory::Manager());

  CustomReactor reactor(dependency_injector);
  reactor.insert(character::Controller::authenticate);
  reactor.insert(character::Controller::interact);
  reactor.insert(inventory::Controller::load);
  reactor.insert(movement::Controller::move);
  reactor.insert(character::Controller::logout);
  reactor.insert(character::Controller::disconnect);
  reactor.insert(chat::Controller::say);
  reactor.insert(character::Controller::set_title);
  reactor.insert(inventory::Controller::move_item);


  Deserializer deserializer;
  deserializer.insert<character::commands::Authenticate>(2);
  deserializer.insert<inventory::commands::LoadInventory>(3);
  deserializer.insert<movement::commands::Move>(4);
  deserializer.insert<chat::Say>(14);
  deserializer.insert<inventory::commands::MoveItem>(18);
  deserializer.insert<character::commands::Interact>(22);
  deserializer.insert<character::commands::SetTitle>(64);
  deserializer.insert<character::commands::Logout>(313);

  Serializer serializer;
  serializer.insert<entity::Character>(1);
  serializer.insert<character::events::CharacterDetail>(2);
  serializer.insert<movement::events::Move>(5);
  serializer.insert<entity::Destroy>(7);
  serializer.insert<chat::Says>(23);
  serializer.insert<character::events::ShowEmote>(25);
  serializer.insert<inventory::events::LoadInventory>(26);
  serializer.insert<inventory::events::UpdateInventory>(27);
  serializer.insert<entity::events::Update>(29);
  serializer.insert<character::events::TitleChanged>(67);
  serializer.insert<character::events::LoadFunctionBar>(91);


  // CONFIGURE SERVER
  Server server(context, 30001, reactor, serializer, deserializer);
  server.start();

  // START LOOP
  asio::signal_set signals(context, SIGINT, SIGTERM);
  signals.async_wait([&](auto, auto) { context.stop(); });
  context.run();
}
