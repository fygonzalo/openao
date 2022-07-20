
#ifndef OPENAO_GAME_MESSAGES_REQUESTS_MOVEITEM_H
#define OPENAO_GAME_MESSAGES_REQUESTS_MOVEITEM_H

#include <cstdint>
namespace Game::Messages::Requests {

struct MoveItem {

  static const uint16_t type = 0x12;

  uint16_t slot_source;
  uint16_t slot_destination;

  template<typename Archive>
  void deserialize(Archive &archive) {
    archive.read(slot_source);
    archive.read(slot_destination);
  }
};

}// namespace Game::Messages::Requests

#endif// OPENAO_GAME_MESSAGES_REQUESTS_MOVEITEM_H
