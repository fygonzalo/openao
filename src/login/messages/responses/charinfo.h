
#ifndef OPENAO_CHARINFO_H
#define OPENAO_CHARINFO_H

#include "model/account.h"
#include "model/branches.h"
#include "model/characters.h"

#include "login/messages/responses/common/attributes.h"
#include "login/messages/responses/common/branches.h"
#include "login/messages/responses/common/equipment.h"

#include "utils/binarybuffer.h"

namespace Login::Messages::Responses {
class CharInfo {
public:
  static const uint16_t type = 0x00;

  CharInfo(Model::Account &a, Model::Characters &cc, Model::Branches &bb)
      : a_(a), cc_(cc), bb_(bb) {}

  void serialize(BinaryBuffer &buffer) {
    buffer.write((uint16_t) 0);
    buffer.write((uint8_t) 0);

    for (auto &c: cc_.characters) { serialize(buffer, c); }
    buffer.write(cc_.birthday_months);
    buffer.write(cc_.birthday_days);
    buffer.write(cc_.bloods);
    buffer.write(cc_.hps);
    buffer.write(cc_.mps);
    buffer.write(cc_.skills);
    buffer.write(a_.slots);

    Login::Messages::Responses::serialize(buffer, bb_);
  }

private:
  void serialize(BinaryBuffer &buffer, Model::Character &c) {
    buffer.write(c.index);
    buffer.write(c.level);
    buffer.write(c.faction);
    Login::Messages::Responses::serialize(buffer, c.attributes);
    buffer.write(c.stage);
    buffer.set(0, 4);
    buffer.write(c.shape);
    buffer.set(0, 8);
    buffer.write(c.id);
    buffer.write(c.name);
    buffer.write(a_.id);
    buffer.write(a_.username);
    Login::Messages::Responses::serialize(buffer, c.equipment);
    serialize(buffer, c.stats);
    buffer.write(c.title);
    buffer.set(0, 4);
  }

  void serialize(BinaryBuffer &buffer, Model::Stats &s) {
    buffer.write(s.hp_current);
    buffer.set(0, 4);
    buffer.write(s.mp_current);
    buffer.set(0, 4);
  }

  Model::Account &a_;
  Model::Characters &cc_;
  Model::Branches &bb_;
};
}// namespace Login::Messages::Responses

#endif// OPENAO_CHARINFO_H
