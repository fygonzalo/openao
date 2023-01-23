#ifndef OPENAO_GAME_STAGE_MANAGER_H
#define OPENAO_GAME_STAGE_MANAGER_H

#include <unordered_set>

#include "di/injectable.h"
#include "transport/iclient.h"

using namespace openao::framework::transport;

namespace openao::game::stage {

class Manager : public openao::framework::di::Injectable {
public:
  void subscribe(IClient *client) { clients_.insert(client); }

  void broadcast(framework::IEvent &event) {
    for (auto c: clients_) c->send(event);
  }

  void unsubscribe(IClient *client) { clients_.erase(client); };

private:
  std::unordered_set<IClient *> clients_;
};

}// namespace openao::game::stage

#endif// OPENAO_GAME_STAGE_MANAGER_H
