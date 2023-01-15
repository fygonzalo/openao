
#ifndef OPENAO_EXPERIMENTAL_SERIALIZATION_SERIALIZER_H
#define OPENAO_EXPERIMENTAL_SERIALIZATION_SERIALIZER_H

#include <cstdint>
#include <functional>
#include <map>
#include <typeindex>

#include "utils/binarybuffer.h"

namespace openao::experimental::serialization {

class Serializer {

public:
  template<typename T>
  void insert(uint16_t code) {
    index_to_code_[typeid(T)] = code;
    index_to_fun_[typeid(T)] = [code](reactor::IEvent &e) {
      auto t = static_cast<T &>(e);

      BinaryBuffer buffer;
      buffer.write(code);
      buffer.write(t);
      return buffer;
    };
  }

  template<typename T>
  BinaryBuffer serialize(T &t) {
    auto code = index_to_code_[typeid(T)];

    BinaryBuffer buffer;
    buffer.write(code);
    buffer.write(t);

    return buffer;
  }

  BinaryBuffer serialize(std::type_index i, reactor::IEvent &e) {
    auto fun = index_to_fun_[i];
    return fun(e);
  }

private:
  std::map<std::type_index, uint16_t> index_to_code_;
  std::map<std::type_index, std::function<BinaryBuffer(reactor::IEvent &)>>
          index_to_fun_;
};

}// namespace openao::experimental::serialization

#endif// OPENAO_EXPERIMENTAL_SERIALIZATION_SERIALIZER_H
