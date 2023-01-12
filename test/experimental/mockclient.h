
#ifndef OPENAO_TEST_EXPERIMENTAL_MOCKCLIENT_H
#define OPENAO_TEST_EXPERIMENTAL_MOCKCLIENT_H

#include <gmock/gmock.h>

#include "experimental/transport/iclient.h"

using namespace openao::experimental::transport;

class MockClient : public IClient {
public:
  MOCK_METHOD(void, send, (openao::experimental::reactor::IEvent&), (override));
};

#endif// OPENAO_TEST_EXPERIMENTAL_MOCKCLIENT_H
