
#ifndef OPENAO_CHARINFO_H
#define OPENAO_CHARINFO_H

#include "model/account.h"
#include "model/branches.h"
#include "model/characters.h"

#include "serialization/attributes.h"
#include "serialization/branches.h"
#include "serialization/equipment.h"

#include "utils/binarybuffer.h"

namespace Login::Messages::Responses {

struct AuthError {
  static const uint16_t type = 0x00;

  int code;

  template <typename Archive>
  void serialize(Archive& archive) {
    archive.write(code);
  }
};

struct CharInfo {
public:
  static const uint16_t type = 0x00;

  CharInfo(Model::Account &a, Model::Characters &cc, Model::Branches &bb)
      : a_(a), cc_(cc), bb_(bb) {}

  template <typename Archive>
  void serialize(Archive& archive) {
    archive.write((uint16_t) 0);
    archive.write(a_.pin);

    for (auto &c: cc_.characters) { serialize(archive, c); }
    archive.write(cc_.birthday_months);
    archive.write(cc_.birthday_days);
    archive.write(cc_.bloods);
    archive.write(cc_.hps);
    archive.write(cc_.mps);
    for (auto &c: cc_.skills) {
      for (int i = 0; i < 9; i++){
        archive.write(c[i]);
      }
    }
    archive.write(a_.slots);

    Serialization::serialize(archive, bb_);
  }

private:

  void serialize(BinaryBuffer& archive, Model::Character &c) {
    archive.write(c.index);
    archive.write(c.level);
    archive.write(c.faction);
    Serialization::serialize(archive, c.attributes);
    archive.write(c.stage);
    archive.set(0, 4);
    archive.write(c.shape);
    archive.set(0, 8);
    archive.write(c.id);
    archive.write(c.name);
    archive.write(a_.id);
    archive.write(a_.username);
    Serialization::serialize(archive, c.equipment);
    serialize(archive, c.stats);
    archive.write(c.title);
    archive.set(0, 4);
  }

  template <typename Archive>
  void serialize(Archive &archive, Model::Stats &s) {
    archive.write(s.hp_current);
    archive.set(0, 4);
    archive.write(s.mp_current);
    archive.set(0, 4);
  }

  Model::Account &a_;
  Model::Characters &cc_;
  Model::Branches &bb_;
};
}// namespace Login::Messages::Responses

#endif// OPENAO_CHARINFO_H
