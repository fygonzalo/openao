
#ifndef OPENAO_FRAMEWORK_TRANSPORT_ICLIENT_H
#define OPENAO_FRAMEWORK_TRANSPORT_ICLIENT_H

#include "event.h"

namespace openao::framework::transport {

class IClient {
public:
  virtual ~IClient() = default;
  virtual void send(IEvent &event) = 0;

private:
};

}// namespace openao::framework::transport

#endif// OPENAO_FRAMEWORK_TRANSPORT_ICLIENT_H
