
#ifndef OPENAO_SYSTEM_H
#define OPENAO_SYSTEM_H

#include "transport/messagestream.h"
#include <asio.hpp>

using asio::awaitable;

class System {
public:
  virtual awaitable<void> handle(MessageStream stream) = 0;
};

#endif// OPENAO_SYSTEM_H
