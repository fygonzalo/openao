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

  template<typename Archive>
  void serialize(Archive &archive) {
    archive.write(entityid);
    archive.set(0, 4);
    archive.write(c.position.x);
    archive.write(c.position.y);
    archive.write(c.name);
    archive.write(c.title);
    archive.write((uint32_t)1751094);
    archive.write(c.position.orientation);
    archive.write(c.shape);
    Serialization::serialize(archive, c.attributes);
    archive.write(c.faction);
    archive.set(0, 1);// ?
    archive.set(0, 2);// Team ?
    Serialization::serialize(archive, c.equipment);
    // Unk
    archive.write((uint32_t)23190);
    // Badge / Overlay
    archive.write((uint32_t)5367);
    // Quest title
    archive.set(0, 2);
    // Unk
    archive.set(0, 3);
    // League badge and title
    archive.set(0, 1);
    archive.set(0, 12);
    // Unk
    archive.set(0, 6);


  }
};

}// namespace Game::Messages::Responses

#endif// OPENAO_GAME_MESSAGES_RESPONSES_SPAWNPLAYER_H
