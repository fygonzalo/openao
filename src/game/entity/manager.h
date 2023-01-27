#ifndef OPENAO_GAME_ENTITY_MANAGER_H
#define OPENAO_GAME_ENTITY_MANAGER_H

#include <list>
#include <optional>
#include <queue>

#include "di/injectable.h"
#include "entity/model/character.h"
#include "entity/model/npc.h"


namespace openao::game::entity {

class Manager : public openao::framework::di::Injectable {
public:
  Manager() {
    for (auto i = 1; i < 1000; i++) entities_ids_.push(i);
  }

  entity::Character &create() {
    auto id = entities_ids_.front();
    entities_ids_.pop();
    auto &entity = characters_.emplace_back();
    entity.entityid = id;
    return entity;
  }

  entity::NPC &create_npcs() {
    auto id = entities_ids_.front();
    entities_ids_.pop();
    auto &entity = npcs_.emplace_back();
    entity.id = id;
    return entity;
  }

  std::list<entity::Character> &get() { return characters_; }
  std::list<entity::NPC> &get_npcs() { return npcs_; }

  entity::Character *get(uint32_t id) {
    for (auto b = characters_.begin(); b != characters_.end(); ++b) {
      if (b->character_id == id) return &*b;
    }
    return nullptr;
  }

  void remove(uint32_t id) {
    auto iter = characters_.begin();
    for (; iter != characters_.end(); ++iter) {
      if (iter->character_id == id) break;
    }

    if (iter != characters_.end()) {
      entities_ids_.push(iter->entityid);
      characters_.erase(iter);
    }
  }

private:
  std::queue<uint32_t> entities_ids_;
  std::list<entity::Character> characters_;
  std::list<entity::NPC> npcs_;
};

}// namespace openao::game::entity

#endif// OPENAO_GAME_ENTITY_MANAGER_H
