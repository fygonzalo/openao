
#ifndef OPENAO_EXPERIMENTAL_SERIALIZER_SERIALIZER_H
#define OPENAO_EXPERIMENTAL_SERIALIZER_SERIALIZER_H

#include <cstdint>
#include <map>
#include <functional>
#include <typeindex>

#include "utils/binarybuffer.h"

namespace openao::experimental::serializer {

class Serializer {

public:
  template <typename T>
  void insert(uint16_t code) {
    index_to_code_[typeid(T)] = code;
  }

  template <typename T>
  BinaryBuffer serialize(T& t) {
    auto code = index_to_code_[typeid(T)];

    BinaryBuffer buffer;
    buffer.write(code);
    buffer.write(t);

    return buffer;
  }

private:
  //std::map<std::type_index, std::function<void()>> code_to_fun_;
  std::map<std::type_index, uint16_t> index_to_code_;
};

}

#endif// OPENAO_EXPERIMENTAL_SERIALIZER_SERIALIZER_H
