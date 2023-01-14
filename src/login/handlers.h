
#ifndef OPENAO_LOGIN_HANDLERS_H
#define OPENAO_LOGIN_HANDLERS_H

#include <iostream>

#include "transport/client.h"
#include "transport/message.h"

namespace Login {

typedef std::function<void(Client &, Message &)> Handler;

class Handlers {

public:
  template<typename T>
  void add(std::function<void(Client &, const T &)> fun) {
    handlers[T::type] = [fun](Client &c, Message &m) { fun(c, m.read<T>()); };
  }

  Handler &operator[](int code) { return handlers[code]; }


private:
  std::map<int, Handler> handlers;
};

}// namespace Login

#endif// OPENAO_LOGIN_HANDLERS_H
