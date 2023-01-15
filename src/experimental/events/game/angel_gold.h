
#ifndef OPENAO_EXPERIMENTAL_EVENTS_GAME_ANGEL_GOLD_H
#define OPENAO_EXPERIMENTAL_EVENTS_GAME_ANGEL_GOLD_H

#include "experimental/events/event.h"

namespace openao::experimental::events::game {

struct AngelGold : AbstractEvent {

  uint32_t amount{0};

};

}

#endif// OPENAO_EXPERIMENTAL_EVENTS_GAME_ANGEL_GOLD_H
