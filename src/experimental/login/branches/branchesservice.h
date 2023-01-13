
#ifndef OPENAO_EXPERIMENTAL_LOGIN_BRANCHES_BRANCHESSERVICE_H
#define OPENAO_EXPERIMENTAL_LOGIN_BRANCHES_BRANCHESSERVICE_H

#include <cstdint>
#include <vector>

#include "experimental/di/injectable.h"

namespace openao::experimental::login::branches {

class BranchesService : public di::Injectable {
public:
  std::vector<uint32_t> get_branch_statuses() { return {40, 1}; };
};

}// namespace openao::experimental::login::branches

#endif// OPENAO_EXPERIMENTAL_LOGIN_BRANCHES_BRANCHESSERVICE_H
