#ifndef OPENAO_LOGIN_ACCOUNT_EVENTS_ANNOUNCEMENTEVENT_H
#define OPENAO_LOGIN_ACCOUNT_EVENTS_ANNOUNCEMENTEVENT_H

#include <cstdint>
#include <string>

#include "event.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;

namespace openao::login::account::events {

struct AnnouncementEvent : framework::IEvent {

  static const uint16_t type = 12;

  uint32_t expires_on_ts;
  std::string message;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(expires_on_ts);
    buffer.write((uint32_t) message.size() + 1);
    buffer.write(message);
  }
};

}// namespace openao::login::account::events

#endif// OPENAO_LOGIN_ACCOUNT_EVENTS_ANNOUNCEMENTEVENT_H
