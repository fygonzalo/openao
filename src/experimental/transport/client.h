
#ifndef OPENAO_EXPERIMENTAL_TRANSPORT_CLIENT_H
#define OPENAO_EXPERIMENTAL_TRANSPORT_CLIENT_H

#include <memory>

#include "experimental/transport/imessagestream.h"

#include "experimental/serializer/serializer.h"

using namespace openao::experimental::serializer;

namespace openao::experimental::transport {

class Client {
public:
  explicit Client(std::unique_ptr<IMessageStream> stream,
                  Serializer &serializer)
      : stream_(std::move(stream)), serializer_(serializer){};

  template<typename Event>
  void send(Event &event) {
    BinaryBuffer buffer = serializer_.template serialize(event);
    stream_->send(buffer);
  }

  IMessageStream &stream() { return *stream_; }

private:
  std::unique_ptr<IMessageStream> stream_;
  Serializer &serializer_;
};

}// namespace openao::experimental::transport

#endif// OPENAO_EXPERIMENTAL_TRANSPORT_CLIENT_H
