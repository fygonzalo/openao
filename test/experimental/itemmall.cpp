
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "experimental/transport/client.h"
#include "experimental/game/account/accountmanager.h"
#include "experimental/game/itemmall/controller.h"

#include "messagestreammock.h"

using namespace openao::experimental::game::itemmall;
using namespace openao::experimental::game::account;
using namespace openao::experimental;


TEST(ItemMall, OpenMall_Test) {

  Serializer serializer;
  serializer.insert<LoadAngelGoldEvent>(98);

  // Expected generated events
  LoadAngelGoldEvent event;
  event.amount = 300;

  Client sender(std::make_unique<MessageStreamMock>(), serializer);
  auto &msm = static_cast<MessageStreamMock &>(sender.stream());
  EXPECT_CALL(msm, send(serializer.serialize(event))).Times(1);

  // Create player identity
  uint32_t account_id = 1;
  MallService mall_service;
  AccountManager account_manager;
  account_manager.insert(sender, account_id);

  // Create command
  OpenCommand command{};

  // Execute
  ItemMallController::open_mall(sender, command, account_manager, mall_service);
}