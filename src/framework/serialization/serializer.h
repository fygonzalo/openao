
#ifndef OPENAO_FRAMEWORK_SERIALIZATION_SERIALIZER_H
#define OPENAO_FRAMEWORK_SERIALIZATION_SERIALIZER_H

#include <cstdint>
#include <functional>
#include <map>
#include <typeindex>

#include "utils/binarybuffer.h"

namespace openao::framework::serialization {

class Serializer {

public:
  template<typename T>
  void insert(uint16_t code) {
    index_to_code_[typeid(T)] = code;
    index_to_fun_[typeid(T)] = [code](IEvent &e) {
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

  BinaryBuffer serialize(IEvent &e) {
    auto fun = index_to_fun_[typeid(e)];
    return fun(e);
  }

private:
  std::map<std::type_index, uint16_t> index_to_code_;
  std::map<std::type_index, std::function<BinaryBuffer(IEvent &)>>
          index_to_fun_;
};

}// namespace openao::framework::serialization

#endif// OPENAO_FRAMEWORK_SERIALIZATION_SERIALIZER_H
