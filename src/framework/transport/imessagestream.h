
#ifndef OPENAO_FRAMEWORK_TRANSPORT_IMESSAGESTREAM_H
#define OPENAO_FRAMEWORK_TRANSPORT_IMESSAGESTREAM_H

#include "utils/binarybuffer.h"

namespace openao::framework::transport {

class IMessageStream {
public:
  virtual ~IMessageStream() = default;
  virtual void send(BinaryBuffer buffer) = 0;
};

}// namespace openao::framework::transport

#endif// OPENAO_FRAMEWORK_TRANSPORT_IMESSAGESTREAM_H
