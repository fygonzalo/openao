#ifndef OPENAO_LOGIN_ACCOUNT_REDIRECTSERVEREVENT_H
#define OPENAO_LOGIN_ACCOUNT_REDIRECTSERVEREVENT_H

#include <cstdint>

#include "event.h"
#include "utils/binarybuffer.h"
#include "utils/string.h"

using namespace openao::framework::utils;

namespace openao::login::account::events {

struct RedirectServerEvent : framework::IEvent {
  uint32_t session{};
  String ip{15};
  uint16_t port;

  void serialize(BinaryBuffer &archive) {
    archive.set(0, 2);
    archive.write(session);
    archive.set(1, 1);
    archive.write(ip);
    archive.write(port);
    archive.set(0, 5);
  }
};

}// namespace openao::login::account::events

#endif// OPENAO_LOGIN_ACCOUNT_REDIRECTSERVEREVENT_H
