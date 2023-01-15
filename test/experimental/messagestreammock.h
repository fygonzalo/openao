
#ifndef OPENAO_TEST_EXPERIMENTAL_MESSAGESTREAMMOCK_H
#define OPENAO_TEST_EXPERIMENTAL_MESSAGESTREAMMOCK_H

#include <gmock/gmock.h>
#include "experimental/transport/imessagestream.h"

using namespace openao::experimental::transport;

class MessageStreamMock : public IMessageStream {
public:
  MOCK_METHOD(void, send, (BinaryBuffer buffer), (override));
};

#endif// OPENAO_TEST_EXPERIMENTAL_MESSAGESTREAMMOCK_H
