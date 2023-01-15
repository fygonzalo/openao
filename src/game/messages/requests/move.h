
#ifndef OPENAO_GAME_MESSAGES_REQUEST_MOVE_H
#define OPENAO_GAME_MESSAGES_REQUEST_MOVE_H

#include <cstdint>
namespace Game::Messages::Requests {

struct Move {

  static const uint16_t type = 4;

  struct Position {
    uint16_t x;
    uint16_t y;
  };

  Position source;
  Position destination;

  template<typename Archive>
  void deserialize(Archive &archive) {
    archive.read(source.x);
    archive.read(source.y);
    archive.skip(3);
    archive.read(destination.x);
    archive.read(destination.y);
  }
};

}// namespace Game::Messages::Requests

#endif// OPENAO_GAME_MESSAGES_REQUEST_MOVE_H
