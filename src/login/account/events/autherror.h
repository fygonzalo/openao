#ifndef OPENAO_LOGIN_ACCOUNT_EVENTS_AUTHERROR_H
#define OPENAO_LOGIN_ACCOUNT_EVENTS_AUTHERROR_H

#include <cstdint>

#include "event.h"
#include "utils/binarybuffer.h"

using namespace openao::framework::utils;

namespace openao::login::account::events {

struct AuthError : public framework::IEvent {

  uint16_t message_code;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(message_code);
    buffer.write((uint16_t) 0);
  }
};

}// namespace openao::login::account::events

#endif// OPENAO_LOGIN_ACCOUNT_EVENTS_AUTHERROR_H
