
#ifndef OPENAO_EXPERIMENTAL_GAME_ITEMMALL_LOADANGELGOLDEVENT_H
#define OPENAO_EXPERIMENTAL_GAME_ITEMMALL_LOADANGELGOLDEVENT_H

#include "experimental/events/event.h"

namespace openao::experimental::game::itemmall {

struct LoadAngelGoldEvent : public events::Event<98> {

  uint32_t amount;

  void serialize(BinaryBuffer &buffer) override {
    buffer.write(amount);
  }
};


}

#endif// OPENAO_EXPERIMENTAL_GAME_ITEMMALL_LOADANGELGOLDEVENT_H
