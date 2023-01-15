
#ifndef OPENAO_EXPERIMENTAL_PLAYER_H
#define OPENAO_EXPERIMENTAL_PLAYER_H

#include "experimental/serializer/serializer.h"

using namespace openao::experimental::serializer;

namespace openao::experimental {

class Player {
public:
  Player(Serializer &serializer, std::unique_ptr<IClient> &&client)
      : serializer_(serializer), client_(std::move(client)){};

  template<typename T>
  void send(T &t) {
    BinaryBuffer buffer = serializer_.template serialize(t);
  }

private:
  std::unique_ptr<IClient> client_;
  Serializer &serializer_;
};

}// namespace openao::experimental

#endif// OPENAO_EXPERIMENTAL_PLAYER_H
