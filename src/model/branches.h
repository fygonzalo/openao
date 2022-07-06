
#ifndef OPENAO_BRANCHES_H
#define OPENAO_BRANCHES_H

#include "transport/binarybuffer.h"
#include <cstdint>
#include <utility>
#include <vector>

namespace Model {
  struct Branches {
    Branches() {};
    Branches(std::vector<uint32_t> s) : statuses(std::move(s)) {};

    std::vector<uint32_t> statuses;

  };
}// namespace Model

#endif// OPENAO_BRANCHES_H
