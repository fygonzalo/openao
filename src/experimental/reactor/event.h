
#ifndef OPENAO_EXPERIMENTAL_REACTOR_EVENT_H
#define OPENAO_EXPERIMENTAL_REACTOR_EVENT_H

#include <typeindex>

namespace openao::experimental::reactor {

struct IEvent {
  virtual ~IEvent() = default;
  virtual std::type_index index() const = 0;
};

template<typename T>
struct Event : IEvent {
  virtual std::type_index index() const override { return typeid(*this); }
};

}// namespace openao::experimental::reactor

#endif// OPENAO_EXPERIMENTAL_REACTOR_EVENT_H
