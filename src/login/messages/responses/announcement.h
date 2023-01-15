
#ifndef OPENAO_LOGIN_MESSAGES_RESPONSES_ANNOUNCEMENT_H
#define OPENAO_LOGIN_MESSAGES_RESPONSES_ANNOUNCEMENT_H

#include "utils/binarybuffer.h"
#include <cstdint>

namespace Login::Messages::Responses {

struct Announcement {

  static const uint16_t type = 12;

  uint32_t timestamp = 1693013624;
  std::string message;

  void serialize(BinaryBuffer& buffer) {
    buffer.write(timestamp);
    buffer.write((uint32_t)message.size() + 1);
    buffer.write(message);
  }

};

}

#endif// OPENAO_LOGIN_MESSAGES_RESPONSES_ANNOUNCEMENT_H
