
#ifndef OPENAO_STRING_H
#define OPENAO_STRING_H

#include <string>

#include "binarybuffer.h"

class String {
public:
  String(int size) {
    value_.resize(size);
    size_ = size;
  }

  template<int N>
  String(int size, const char (&str)[N]) {
    value_.resize(size);
    size_ = size;
    memcpy(value_.data(), str, N);
  };

  // Would be nice to have static assertion on the size
  void operator=(const std::string string) {
    int size = string.size();

    if (size > size_) size = size_;

    memcpy(value_.data(), string.data(), size);
  }

  template<std::size_t N>
  void operator=(const char src[N]) {
    memcpy(value_.data(), src, N);
  }

  operator std::string() const { return value_; }

  void serialize(BinaryBuffer &buffer) {
    buffer.write(value_.data(), size_ + 1);
  }

  void deserialize(BinaryBuffer &buffer) { buffer.read(value_); }

private:
  int size_ = 0;
  std::string value_;
};

#endif// OPENAO_STRING_H
