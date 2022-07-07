
#ifndef OPENAO_ACCOUNT_H
#define OPENAO_ACCOUNT_H

#include "utils/string.h"
#include <string>

namespace Model {
struct Account {
  uint32_t id;
  String username{20};
  uint32_t slots;
  bool enabled;
  bool banned;
};
}// namespace Model

#endif// OPENAO_ACCOUNT_H
