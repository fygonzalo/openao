
#ifndef OPENAO_EXPERIMENTAL_EVENTS_GAME_CLIENT_CONNECTED_H
#define OPENAO_EXPERIMENTAL_EVENTS_GAME_CLIENT_CONNECTED_H

#include "experimental/events/abstractevent.h"

#include "transport/client.h"

namespace openao::experimental::events::game {

struct ClientConnected : AbstractEvent {

  ClientConnected(Client& client) : client(client) {};

  Client& client;

};

}

#endif// OPENAO_EXPERIMENTAL_EVENTS_GAME_CLIENT_CONNECTED_H
