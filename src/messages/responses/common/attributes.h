
#ifndef OPENAO_MESSAGES_RESPONSES_COMMON_ATTRIBUTES_H
#define OPENAO_MESSAGES_RESPONSES_COMMON_ATTRIBUTES_H

#include "model/character.h"
#include "transport/binarybuffer.h"

namespace Messages::Responses {
  void serialize(BinaryBuffer& buffer, Model::Attributes& a) {
    buffer.write(a.gender);
    buffer.write(a.hair_style);
    buffer.write(a.height);
    buffer.write(a.hair_color);
    buffer.write(a.skin_color);
  }
}

#endif// OPENAO_MESSAGES_RESPONSES_COMMON_ATTRIBUTES_H
