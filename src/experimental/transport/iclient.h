
#ifndef OPENAO_EXPERIMENTAL_TRANSPORT_ICLIENT_H
#define OPENAO_EXPERIMENTAL_TRANSPORT_ICLIENT_H

#include "experimental/reactor/event.h"

namespace openao::experimental::transport {

class IClient {
public:
  virtual ~IClient() = default;
  virtual void send(reactor::IEvent &event) = 0;

private:
};

}// namespace openao::experimental::transport

#endif// OPENAO_EXPERIMENTAL_TRANSPORT_ICLIENT_H
