
#ifndef OPENAO_EXPERIMENTAL_EVENTS_EVENT_H
#define OPENAO_EXPERIMENTAL_EVENTS_EVENT_H

#include <cstdint>

#include "experimental/events/abstractevent.h"

namespace openao::experimental::events {

template<uint16_t CODE>
struct Event : public AbstractEvent {
  uint16_t code() const override { return CODE; };
};

}// namespace openao::experimental::events

#endif// OPENAO_EXPERIMENTAL_EVENTS_EVENT_H
