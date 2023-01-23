#ifndef OPENAO_GAME_ENTITY_MANAGER_H
#define OPENAO_GAME_ENTITY_MANAGER_H

#include <list>
#include <optional>
#include <queue>

#include "di/injectable.h"
#include "entity/model/character.h"


namespace openao::game::entity {

class Manager : public openao::framework::di::Injectable {
public:
  Manager() {
    for (auto i = 0; i < 1000; i++) entities_ids_.push(i);
  }

  entity::Character &create() {
    auto id = entities_ids_.front();
    entities_ids_.pop();
    auto &entity = characters_.emplace_back();
    entity.entityid = id;
    return entity;
  }

  std::list<entity::Character> &get() { return characters_; }

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
};

}// namespace openao::game::entity

#endif// OPENAO_GAME_ENTITY_MANAGER_H
