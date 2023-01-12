
#ifndef OPENAO_EXPERIMENTAL_SERIALIZATION_DESERIALIZER_H
#define OPENAO_EXPERIMENTAL_SERIALIZATION_DESERIALIZER_H

#include <cassert>
#include <map>
#include <typeindex>
#include <unordered_set>

#include "experimental/reactor/event.h"
#include "utils/binarybuffer.h"

namespace openao::experimental::serialization {


class Deserializer {
public:

  typedef std::pair<std::type_index, std::unique_ptr<reactor::IEvent>> Result;

  template<typename T>
  void insert(uint16_t code) {
    codes_[typeid(T)] = code;

    fun_[code] = [](BinaryBuffer& buffer) {
      auto t = buffer.read<T>();
      std::type_index idx = typeid(T);
      return std::pair<std::type_index, std::unique_ptr<T>>(idx, std::make_unique<T>(t));
    };

  }

  template <typename T>
  T deserialize(BinaryBuffer& buffer) {
    buffer.read<uint16_t>();
    return buffer.read<T>();
  }

  Result deserialize(BinaryBuffer& buffer) {
    auto code = buffer.read<uint16_t>();
    return fun_[code](buffer);
  }

private:
  std::unordered_map<std::type_index, uint16_t> codes_{};
  std::unordered_map<uint16_t, std::function<Result(BinaryBuffer &buffer)>> fun_{};
};

}// namespace openao::experimental::serializer

#endif// OPENAO_EXPERIMENTAL_SERIALIZATION_DESERIALIZER_H
