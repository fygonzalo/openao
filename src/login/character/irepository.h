#ifndef OPENAO_LOGIN_CHARACTER_IREPOSITORY_H
#define OPENAO_LOGIN_CHARACTER_IREPOSITORY_H

#include <vector>

#include "character/model/info.h"
#include "di/injectable.h"

namespace openao::login::character {

class IRepository : public framework::di::Injectable {
public:
  virtual ~IRepository() = default;

  virtual std::vector<model::Info> get(int account_id) = 0;
};

}// namespace openao::login::character

#endif// OPENAO_LOGIN_CHARACTER_IREPOSITORY_H
