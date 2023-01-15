
#ifndef OPENAO_TEST_EXPERIMENTAL_CLIENTMOCK_H
#define OPENAO_TEST_EXPERIMENTAL_CLIENTMOCK_H

#include <gmock/gmock.h>

#include "experimental/events/abstractevent.h"
#include "experimental/iclient.h"

using namespace openao::experimental;
using namespace openao::experimental::game;

class MockClient : public IClient {
public:
  MOCK_METHOD(void, send, (openao::experimental::events::AbstractEvent& event), (override));
};

#endif// OPENAO_TEST_EXPERIMENTAL_CLIENTMOCK_H
