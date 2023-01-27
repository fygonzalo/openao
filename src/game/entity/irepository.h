#ifndef OPENAO_GAME_ENTITY_IREPOSITORY_H
#define OPENAO_GAME_ENTITY_IREPOSITORY_H

#include <list>

#include "di/injectable.h"
#include "entity/model/npc.h"

namespace openao::game::entity {

class IRepository : public framework::di::Injectable {
public:
  virtual std::list<NPC> get_npcs_by_stage(int stage) = 0;
};

}// namespace openao::game::entity

#endif// OPENAO_GAME_ENTITY_IREPOSITORY_H
