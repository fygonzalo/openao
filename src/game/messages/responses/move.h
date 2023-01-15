
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_MOVE_H
#define OPENAO_GAME_MESSAGES_RESPONSES_MOVE_H

#include <cstdint>
namespace Game::Messages::Responses {

struct Move {
  static const uint16_t type = 5;

  struct Position {
    uint32_t x;
    uint32_t y;
  };

  uint32_t entityid;
  Position source;
  Position destination;
  uint16_t speed;

  template<typename Archive>
  void serialize(Archive &archive) {
    archive.write(entityid);
    archive.write(source.x);
    archive.write(source.y);
    archive.write(destination.x);
    archive.write(destination.y);
    archive.write(speed);
  }
};

}// namespace Game::Messages::Responses

#endif// OPENAO_GAME_MESSAGES_RESPONSES_MOVE_H
