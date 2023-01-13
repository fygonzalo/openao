
#include <gtest/gtest.h>

#include "experimental/login/account/characterlistevent.h"

using namespace openao::experimental::login::account;

TEST(Account, CharacterListEvent_Serialization_Test) {

  CharacterListEvent character_list_event;

  BinaryBuffer buffer;
  character_list_event.serialize(buffer);

  ASSERT_EQ(629, buffer.size());
}