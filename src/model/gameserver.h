
#ifndef OPENAO_GAMESERVER_H
#define OPENAO_GAMESERVER_H
#include "transport/string.h"
namespace Model {
  struct GameServer {
    String ip{15};
    uint16_t port;
  };
}

#endif// OPENAO_GAMESERVER_H
