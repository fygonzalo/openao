
#include <gtest/gtest.h>

#include "experimental/login/account/characterlistevent.h"

using namespace openao::experimental::login::account;

TEST(Account, CharacterListEvent_Serialization_Test) {

  CharacterListEvent character_list_event;

  BinaryBuffer buffer;
  character_list_event.serialize(buffer);

  ASSERT_EQ(629, buffer.size());
}

TEST(Account, CharacterListEvent_Serialization_WithBranches_Test) {

  CharacterListEvent character_list_event;
  character_list_event.branches = CharacterListEvent::Branches{{40, 2}};

  BinaryBuffer buffer;
  character_list_event.serialize(buffer);

  ASSERT_EQ(637, buffer.size());
}