
#ifndef OPENAO_TEST_EXPERIMENTAL_MOCKMESSAGESTREAM_H
#define OPENAO_TEST_EXPERIMENTAL_MOCKMESSAGESTREAM_H

#include "experimental/transport/imessagestream.h"
#include <gmock/gmock.h>

using namespace openao::experimental::transport;

class MessageStreamMock : public IMessageStream {
public:
  MOCK_METHOD(void, send, (BinaryBuffer buffer), (override));
};

#endif// OPENAO_TEST_EXPERIMENTAL_MOCKMESSAGESTREAM_H
