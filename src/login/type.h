
#ifndef OPENAO_TYPE_H
#define OPENAO_TYPE_H

#include <cstdint>

enum class RequestType : uint16_t {
  AUTH = 0x02,
};

enum class ResponseType : uint16_t {
  AUTH = 0x00,
  REDIRECT = 0x04,
};

#endif// OPENAO_TYPE_H
