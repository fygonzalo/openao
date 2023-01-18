#ifndef OPENAO_LOGIN_ACCOUNT_REPOSITORY_CHARACTERINFO_H
#define OPENAO_LOGIN_ACCOUNT_REPOSITORY_CHARACTERINFO_H

#include <string>

namespace openao::login::account::repository {

struct Equipment {
  uint32_t head{0};
  uint32_t body{0};
  uint32_t right_hand{0};
  uint32_t left_hand{0};
  uint32_t hand{0};
  uint32_t feet{0};
  uint32_t back{0};
  uint32_t ride{0};
};

struct Character {

  int id;
  int account_id;

  std::string name;
  std::string title;

  int level;
  int stage;
  int shape;
  int faction;

  Equipment equipment;
};


}// namespace openao::login::account::repository

#endif// OPENAO_LOGIN_ACCOUNT_REPOSITORY_CHARACTERINFO_H
