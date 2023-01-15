
#ifndef OPENAO_EXPERIMENTAL_EVENTS_ABSTRACTEVENT_H
#define OPENAO_EXPERIMENTAL_EVENTS_ABSTRACTEVENT_H

#include "utils/binarybuffer.h"

namespace openao::experimental::events {


struct AbstractEvent {
  virtual ~AbstractEvent() = default;
  virtual void serialize(BinaryBuffer &buffer) = 0;
  virtual uint16_t code() const = 0;

};
}// namespace openao::experimental

#endif// OPENAO_EXPERIMENTAL_EVENTS_ABSTRACTEVENT_H
