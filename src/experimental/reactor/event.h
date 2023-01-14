
#ifndef OPENAO_EXPERIMENTAL_REACTOR_EVENT_H
#define OPENAO_EXPERIMENTAL_REACTOR_EVENT_H

#include <typeindex>

namespace openao::experimental::reactor {

struct IEvent {
  virtual ~IEvent() = default;
};


}// namespace openao::experimental::reactor

#endif// OPENAO_EXPERIMENTAL_REACTOR_EVENT_H
