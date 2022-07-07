
#ifndef OPENAO_GAMESERVER_H
#define OPENAO_GAMESERVER_H
#include "utils/string.h"
namespace Model {
struct GameServer {
  String ip{15};
  uint16_t port;
};
}// namespace Model

#endif// OPENAO_GAMESERVER_H
