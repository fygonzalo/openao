#ifndef OPENAO_LOGIN_CHARACTER_MODEL_INFO_H
#define OPENAO_LOGIN_CHARACTER_MODEL_INFO_H

#include <string>

namespace openao::login::character::model {

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

struct Info {

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


}// namespace openao::login::character::model

#endif// OPENAO_LOGIN_CHARACTER_MODEL_INFO_H
