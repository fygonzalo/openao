
#ifndef OPENAO_GAME_H
#define OPENAO_GAME_H

#include <queue>

#include "transport/messagestream.h"

class Event {};



class Game {
public:
  /**
   * Must be thread safe
   * @param e
   */
  void dispatch(Event e) {
          // process msg
  };

  void simulation() {

  }


private:
};

#endif// OPENAO_GAME_H
