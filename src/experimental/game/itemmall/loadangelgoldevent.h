
#ifndef OPENAO_EXPERIMENTAL_GAME_ITEMMALL_LOADANGELGOLDEVENT_H
#define OPENAO_EXPERIMENTAL_GAME_ITEMMALL_LOADANGELGOLDEVENT_H



namespace openao::experimental::game::itemmall {

struct LoadAngelGoldEvent : reactor::Event<LoadAngelGoldEvent> {

  uint32_t amount;

  void serialize(BinaryBuffer &buffer) {
    buffer.write(amount);
  }
};


}

#endif// OPENAO_EXPERIMENTAL_GAME_ITEMMALL_LOADANGELGOLDEVENT_H
