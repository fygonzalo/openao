
#ifndef OPENAO_EXPERIMENTAL_TRANSPORT_CLIENT_H
#define OPENAO_EXPERIMENTAL_TRANSPORT_CLIENT_H

#include <memory>

#include "experimental/transport/iclient.h"
#include "experimental/transport/imessagestream.h"

#include "experimental/reactor.h"
#include "experimental/serialization/deserializer.h"
#include "experimental/serialization/serializer.h"

using namespace openao::experimental::serialization;

namespace openao::experimental::transport {


class Client : public IClient {
public:
  Client(std::unique_ptr<IMessageStream> stream, Reactor &reactor,
                  Serializer &serializer, Deserializer &deserializer)
      : stream_(std::move(stream)), reactor_(reactor), serializer_(serializer),
        deserializer_(deserializer){};

  void send(reactor::IEvent &event) override {
    BinaryBuffer buffer = serializer_.serialize(event.index(), event);
    stream_->send(buffer);
  }

  void recv(BinaryBuffer &buffer) {
    auto [t, e] = deserializer_.deserialize(buffer);
    reactor_.react(t, *e);
  }

  IMessageStream &stream() { return *stream_; }

protected:
  std::unique_ptr<IMessageStream> stream_;
  Serializer &serializer_;
  Deserializer &deserializer_;
  Reactor &reactor_;
};

}// namespace openao::experimental::transport

#endif// OPENAO_EXPERIMENTAL_TRANSPORT_CLIENT_H
