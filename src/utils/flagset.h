
#ifndef OPENAO_UTILS_FLAGSET_H
#define OPENAO_UTILS_FLAGSET_H

// flag_set is a type-safe class for using enums as flags in C++14 with an
// underlying std::bitset. See https://github.com/mrts/flag-set-cpp Licence:
// MIT, see LICENCE

#pragma once

#include <bitset>
#include <cassert>
#include <iostream>
#include <string>

template<typename T>
class FlagSet {
public:
  FlagSet() = default;

  explicit FlagSet(const T &val) { flags.set(static_cast<u_type>(val)); }

  // Binary operations.

  FlagSet &operator&=(const T &val) noexcept {
    bool tmp = flags.test(static_cast<u_type>(val));
    flags.reset();
    flags.set(static_cast<u_type>(val), tmp);
    return *this;
  }

  FlagSet &operator&=(const FlagSet &o) noexcept {
    flags &= o.flags;
    return *this;
  }

  FlagSet &operator|=(const T &val) noexcept {
    flags.set(static_cast<u_type>(val));
    return *this;
  }

  FlagSet &operator|=(const FlagSet &o) noexcept {
    flags |= o.flags;
    return *this;
  }

  // The resulting bitset can contain at most 1 bit.
  FlagSet operator&(const T &val) const {
    FlagSet ret(*this);
    ret &= val;

    assert(ret.flags.count() <= 1);
    return ret;
  }

  FlagSet operator&(const FlagSet &val) const {
    FlagSet ret(*this);
    ret.flags &= val.flags;

    return ret;
  }

  // The resulting bitset contains at least 1 bit.
  FlagSet operator|(const T &val) const {
    FlagSet ret(*this);
    ret |= val;

    assert(ret.flags.count() >= 1);
    return ret;
  }

  FlagSet operator|(const FlagSet &val) const {
    FlagSet ret(*this);
    ret.flags |= val.flags;

    return ret;
  }

  FlagSet operator~() const {
    FlagSet cp(*this);
    cp.flags.flip();

    return cp;
  }

  // The bitset evaluates to true if any bit is set.
  explicit operator bool() const { return flags.any(); }

  // Methods from std::bitset.

  bool operator==(const FlagSet &o) const { return flags == o.flags; }

  std::size_t size() const { return flags.size(); }

  std::size_t count() const { return flags.count(); }

  FlagSet &set() {
    flags.set();
    return *this;
  }

  FlagSet &reset() {
    flags.reset();
    return *this;
  }

  FlagSet &flip() {
    flags.flip();
    return *this;
  }

  FlagSet &set(const T &val, bool value = true) {
    flags.set(static_cast<u_type>(val), value);
    return *this;
  }

  FlagSet &reset(const T &val) {
    flags.reset(static_cast<u_type>(val));
    return *this;
  }

  FlagSet &flip(const T &val) {
    flags.flip(static_cast<u_type>(val));
    return *this;
  }

  constexpr bool operator[](const T &val) const {
    return flags[static_cast<u_type>(val)];
  }

  std::string to_string() const { return flags.to_string(); }

  // Operator for outputting to std::ostream.
  friend std::ostream &operator<<(std::ostream &stream, const FlagSet &self) {
    return stream << self.flags;
  }

  void serialize(BinaryBuffer &buffer) const {
    buffer.write(static_cast<u_type>(flags.to_ullong()));
  }

  void deserialize(BinaryBuffer &buffer) {
    buffer.read(static_cast<u_type>(flags.to_ullong()));
  }

private:
  using u_type = std::underlying_type_t<T>;

  // _ is last value sentinel and must be present in enum T.
  std::bitset<static_cast<u_type>(T::_)> flags;
};

template<typename T, typename = void>
struct is_enum_that_contains_sentinel : std::false_type {};

template<typename T>
struct is_enum_that_contains_sentinel<T, decltype(static_cast<void>(T::_))>
    : std::is_enum<T> {};

// Operator that combines two enumeration values into a flag_set only if the
// enumeration contains the sentinel `_`.
template<typename T>
std::enable_if_t<is_enum_that_contains_sentinel<T>::value, FlagSet<T>>
operator|(const T &lhs, const T &rhs) {
  FlagSet<T> fs;
  fs |= lhs;
  fs |= rhs;

  return fs;
}


#endif// OPENAO_UTILS_FLAGSET_H
