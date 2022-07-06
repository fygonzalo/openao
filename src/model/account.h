
#ifndef OPENAO_ACCOUNT_H
#define OPENAO_ACCOUNT_H

#include <string>
#include "transport/string.h"

namespace Model {
  struct Account {
    uint32_t id;
    String username{20};
    uint32_t slots;
    bool enabled;
    bool banned;
  };
}

#endif// OPENAO_ACCOUNT_H
