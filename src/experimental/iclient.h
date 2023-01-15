
#ifndef OPENAO_EXPERIMENTAL_GAME_ICLIENT_H
#define OPENAO_EXPERIMENTAL_GAME_ICLIENT_H

#include <cstdio>

#include "experimental/events/abstractevent.h"

namespace openao::experimental {

class IClient {
public:
  virtual ~IClient() = default;
  virtual void send(experimental::events::AbstractEvent& event) = 0;
};

}

#endif// OPENAO_EXPERIMENTAL_GAME_ICLIENT_H
