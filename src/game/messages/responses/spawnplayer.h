#ifndef OPENAO_GAME_MESSAGES_RESPONSES_SPAWNPLAYER_H
#define OPENAO_GAME_MESSAGES_RESPONSES_SPAWNPLAYER_H

#include <cstdint>

#include "model/character.h"
#include "serialization/attributes.h"
#include "serialization/equipment.h"

namespace Game::Messages::Responses {

struct SpawnPlayer {
  static const uint16_t type = 0x01;

  uint32_t entityid;
  Model::Character c;

  template <typename Archive>
  void serialize(Archive& archive) {
    archive.write(entityid);
    archive.write(c.position.orientation);
    archive.write(c.position.x);
    archive.write(c.position.y);
    archive.write(c.name);
    archive.write(c.title);
    archive.set(0, 9);
    Serialization::serialize(archive, c.attributes);
    archive.write(c.faction);
    archive.set(0, 1); // ?
    archive.set(0, 2); // Team ?
    Serialization::serialize(archive, c.equipment);
    archive.set(0, 13);
    archive.set(0, 13); // League ?
    archive.set(0, 6);
  }

};

}

#endif// OPENAO_GAME_MESSAGES_RESPONSES_SPAWNPLAYER_H
