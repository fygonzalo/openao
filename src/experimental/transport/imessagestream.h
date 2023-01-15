
#ifndef OPENAO_EXPERIMENTAL_TRANSPORT_IMESSAGESTREAM_H
#define OPENAO_EXPERIMENTAL_TRANSPORT_IMESSAGESTREAM_H

#include "utils/binarybuffer.h"

namespace openao::experimental::transport {

class IMessageStream {
public:
  virtual ~IMessageStream() = default;
  virtual void send(BinaryBuffer buffer) = 0;
};

}// namespace openao::experimental::transport

#endif// OPENAO_EXPERIMENTAL_TRANSPORT_IMESSAGESTREAM_H
