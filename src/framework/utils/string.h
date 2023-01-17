
#ifndef OPENAO_FRAMEWORK_UTILS_STRING_H
#define OPENAO_FRAMEWORK_UTILS_STRING_H

#include <string>

#include "utils/binarybuffer.h"

namespace openao::framework::utils {

/*
 * Fixed size C string container.
 *
 * Use it instead of std::string if need to enforce a fixed maximum size.
 * Use it instead of a char array to automatically manage null character.
 *
 */
class String {
public:
  String(int size) {
    value_.resize(size);
    size_ = size;
  }

  template<int N>
  explicit String(const char (&str)[N]) {
    value_.resize(N);
    size_ = N;
    memcpy(value_.data(), str, N);
  }

  /*
   * Truncates the input if it's larger than the container
   */
  String &operator=(const std::string &string) {
    int size = string.size();
    if (size > size_) size = size_;

    memcpy(value_.data(), string.data(), size);
    return *this;
  }

  /*
   * Truncates the input if it's larger than the container
   */
  template<std::size_t N>
  String &operator=(const char src[N]) {
    int size = N;
    if (size > size_) size = size_;

    memcpy(value_.data(), src, size);
    return *this;
  }

  operator std::string() const { return value_; }

  [[nodiscard]] const char *c_str() const { return value_.c_str(); }

  void serialize(BinaryBuffer &buffer) { buffer.write(value_); }
  void serialize(BinaryBuffer &buffer) const { buffer.write(value_); }

  void deserialize(BinaryBuffer &buffer) {
    buffer.read(value_.data(), size_);
    buffer.skip(1);
  }

private:
  int size_ = 0;
  std::string value_;
};

}// namespace openao::framework::utils

#endif// OPENAO_FRAMEWORK_UTILS_STRING_H
