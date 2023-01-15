
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_FRIENDLIST_H
#define OPENAO_GAME_MESSAGES_RESPONSES_FRIENDLIST_H

#include "utils/binarybuffer.h"
#include "utils/string.h"
#include <cstdint>
namespace Game::Messages::Responses {

struct FriendList {

  struct Friend {
    uint32_t charid;
    String nick{16};

    void serialize(BinaryBuffer &buffer) {
      buffer.write(charid);
      buffer.write(nick);
      buffer.set(0, 21);
    }
  };

  static const uint16_t type = 39;

  uint32_t charid;
  std::vector<Friend> friends;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(charid);
    buffer.write((uint32_t) friends.size());
    buffer.write(friends);
  }
};

}// namespace Game::Messages::Responses

#endif// OPENAO_GAME_MESSAGES_RESPONSES_FRIENDLIST_H
