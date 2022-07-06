
#ifndef OPENAO_MESSAGES_RESPONSES_COMMON_EQUIPMENT_H
#define OPENAO_MESSAGES_RESPONSES_COMMON_EQUIPMENT_H

#include "model/character.h"
#include "transport/binarybuffer.h"

namespace Login::Messages::Responses {
void serialize(BinaryBuffer &buffer, Model::Equipment &e) {
  buffer.write(e.head);
  buffer.write(e.body);
  buffer.write(e.main_hand);
  buffer.write(e.off_hand);
  buffer.write(e.hand);
  buffer.write(e.feet);
  buffer.write(e.back);
  buffer.write(e.ride);
}
}// namespace Login::Messages::Responses

#endif// OPENAO_MESSAGES_RESPONSES_COMMON_EQUIPMENT_H
