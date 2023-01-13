
#ifndef OPENAO_EXPERIMENTAL_LOGIN_BRANCHES_BRANCHESSERVICE_H
#define OPENAO_EXPERIMENTAL_LOGIN_BRANCHES_BRANCHESSERVICE_H

#include <cstdint>
#include <vector>

namespace openao::experimental::login::branches {

class BranchesService {

public:
  std::vector<uint32_t> get_branch_statuses() { return {40, 1}; };
};

}// namespace openao::experimental::login::branches

#endif// OPENAO_EXPERIMENTAL_LOGIN_BRANCHES_BRANCHESSERVICE_H
