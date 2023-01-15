
#ifndef OPENAO_GAME_MESSAGES_RESPONSES_LOADINVENTORY_H
#define OPENAO_GAME_MESSAGES_RESPONSES_LOADINVENTORY_H

#include <vector>

#include "model/inventoryitem.h"

namespace Game::Messages::Responses {

struct LoadInventory {

  static const uint16_t type = 0x1A;

  Model::Inventory items;

  template<typename Archive>
  void serialize(Archive &archive) {
    archive.write((uint32_t) items.count());
    for (const Model::InventoryItem &i: items) {
      // Operation
      // 1: Add item
      // 2: Remove item
      archive.set(1, 1);
      archive.write(i.id);
      archive.write(i.creation_timestamp);
      archive.write(i.item);
      for (auto& e: i.enhacements) {
        archive.write(((uint32_t)e.attribute << 26) | e.amount);
      }

      archive.write(i.inventory_type);
      archive.write(i.entity);
      archive.write(i.slot);
      archive.write(i.quantity);
      archive.set(0, 1);
      archive.write(i.hardiness);
      archive.write(i.timer);
      // Extension
      archive.write((uint16_t)0);
      // Footer?
      archive.write(i.bind);
      archive.write(i.rests);
      archive.write(i.flags);
      // Unknown
      archive.set(0, 2);
      // Gems
      for (auto& g: i.gems) {
        archive.write(g << 8);
      }
      // Unknown
      archive.set(0x0, 1);
      archive.write(i.piercings);
      // Enhace count
      archive.write(i.intensifications);
      // Unknown
      archive.set(0, 2);

      // Extension
      // CURRENT HP
      //archive.write((uint32_t)128);
      // CURRENT EXP
      //archive.write((uint64_t)23);
      // REQUIRED EXP
      //archive.write((uint64_t)79);

      //String name{12};
      //name = "/c$5Hope";
      //archive.write(name);
      // TOTAL HP
      //archive.write((uint32_t)129);
      // CURRENT MP
      //archive.write((uint32_t)98);
      // TOTAL MP
      //archive.write((uint32_t)99);
      // ANTETYPE
      //archive.write((uint16_t)3036);
      // LEVEL
      //archive.write((uint32_t)2);

      // SATIATION
      //archive.write((uint16_t)100);
      // INTIMACY
      //archive.write((uint8_t)0xffff);

      // CURRENT EXP DIAMOND
      //archive.write((uint32_t)0);

      // TOTAL EXP DIAMOND
      //archive.write((uint32_t)0);


      // MAXIMUM HP ATTRIB
      //archive.write((uint32_t)0);

      // MAXIMUM MP
      //archive.write((uint32_t)0);

      // ATTACK
      //archive.write((int32_t)0);
      // DEFENSE
      //archive.write((int32_t)0);

      // SPELL ATTACK
      //archive.write((int32_t)0);

      // SPELL DEFENSE
      //archive.write((int32_t)0);

      // RIGOR
      //archive.write((int32_t)0xffffffff);

      // AGILITY
      //archive.write((int32_t)0);


      // THUNDERBOLT ATTACK
      //archive.write((int32_t)0);

      // FIRE ATTACK
      //archive.write((int32_t)0);

      // ICE ATTACK
      //archive.write((int32_t)0);

      // ROTTEN ATTACK
      //archive.write((int32_t)0);

      // PROBABLY ELEMENTAL DEFENSES
      //archive.set(2, 16);

      // STAMINA DEFENSE
      //archive.write((int32_t)0x0fffffff);
      // SOUL DEFENSE
      //archive.write((int32_t)32);
      // UNKNOWN
      //archive.write((uint8_t)0xff);
      // STAR LEVEL
      //archive.write((uint32_t)0);
      // MONSTER ANTETYPE
      //archive.write((uint32_t)0);
      // UNKNOWN
      //archive.write((uint8_t)0);
      //archive.set(0xff, 33);
    }
  }
};

}// namespace Game::Messages::Responses

#endif// OPENAO_GAME_MESSAGES_RESPONSES_LOADINVENTORY_H
