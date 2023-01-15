
#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>


#include "experimental/game/itemmall/controller.h"

#include "clientmock.h"

using namespace openao::experimental::game::itemmall;

class LoadAngelGoldEventEqMatcher {
public:
  using is_gtest_matcher = void;

  explicit LoadAngelGoldEventEqMatcher(const LoadAngelGoldEvent expected)
      : expected_(expected) {}

  bool MatchAndExplain(const openao::experimental::events::AbstractEvent& event, std::ostream*) const {
    if (event.code() != 98)
      return false;

    auto& invoked = static_cast<const LoadAngelGoldEvent&>(event);
    return invoked.amount == expected_.amount;
  }

  void DescribeTo(std::ostream* os) const {
    *os << "Events are equal";
  }

  void DescribeNegationTo(std::ostream* os) const {
    *os << "Events differ";
  }

private:
  const LoadAngelGoldEvent expected_;
};

::testing::Matcher<const LoadAngelGoldEvent&> LoadAngelGoldEventEq(const LoadAngelGoldEvent expected) {
  return LoadAngelGoldEventEqMatcher(expected);
}

TEST(ItemMall, OpenMall_Test) {

  // Expected generated events
  LoadAngelGoldEvent event;
  event.amount = 300;

  // Configure sender
  MockClient sender;
  EXPECT_CALL(sender,
              send(LoadAngelGoldEventEqMatcher(event)))
          .Times(1);

  // Create player identity
  uint32_t account_id = 1;
  MallService mall_service;
  AccountManager account_manager;
  account_manager.insert((IClient&)sender, account_id);


  // Create command
  OpenCommand command{};

  // Execute
  ItemMallController::open_mall(sender, command, account_manager, mall_service);
}