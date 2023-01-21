#ifndef OPENAO_GAME_CHARACTER_MANAGER_H
#define OPENAO_GAME_CHARACTER_MANAGER_H

#include <unordered_map>

#include "di/injectable.h"
#include "transport/iclient.h"

using namespace openao::framework::transport;

namespace openao::game::character {

class Manager : public openao::framework::di::Injectable {
public:
  uint32_t &operator[](IClient *client) { return client_to_char_[client]; }


private:
  std::unordered_map<IClient *, uint32_t> client_to_char_{};
};

}// namespace openao::game::character


#endif// OPENAO_GAME_CHARACTER_MANAGER_H