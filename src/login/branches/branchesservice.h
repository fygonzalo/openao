
#ifndef OPENAO_LOGIN_BRANCHES_BRANCHESSERVICE_H
#define OPENAO_LOGIN_BRANCHES_BRANCHESSERVICE_H

#include <cstdint>
#include <vector>

namespace openao::login::branches {

class BranchesService {

public:
  std::vector<uint32_t> get_branch_statuses() { return {40, 1}; };
};

}// namespace openao::login::branches

#endif// OPENAO_LOGIN_BRANCHES_BRANCHESSERVICE_H
