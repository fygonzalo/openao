
#ifndef OPENAO_LOGIN_MESSAGES_REQUESTS_CREATE_CHAR_H
#define OPENAO_LOGIN_MESSAGES_REQUESTS_CREATE_CHAR_H

#include <cstdint>

#include "serialization/attributes.h"
#include "serialization/misc.h"
#include "utils/string.h"


namespace Login::Messages::Requests {

struct CreateChar {
  Model::Attributes attributes;
  String name{17};
  Model::Misc misc;

  template <typename Archive>
  void deserialize(Archive& archive) {
    archive.skip(1);
    deserialize(archive, attributes);
    archive.read(name);
    archive.skip(27);
    deserialize(archive, misc);
  }
};

}

#endif// OPENAO_LOGIN_MESSAGES_REQUESTS_CREATE_CHAR_H
