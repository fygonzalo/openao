
#ifndef OPENAO_EXPERIMENTAL_GAME_ITEMMALL_LOADANGELGOLDEVENT_H
#define OPENAO_EXPERIMENTAL_GAME_ITEMMALL_LOADANGELGOLDEVENT_H

#include "utils/binarybuffer.h"

namespace openao::experimental::game::itemmall {

struct LoadAngelGoldEvent : reactor::IEvent {

  uint32_t amount;

  void serialize(BinaryBuffer &buffer) { buffer.write(amount); }
};


}// namespace openao::experimental::game::itemmall

#endif// OPENAO_EXPERIMENTAL_GAME_ITEMMALL_LOADANGELGOLDEVENT_H
