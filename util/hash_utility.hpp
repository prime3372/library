#pragma once

#include <array>
#include <cstddef>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include "random/base.hpp"
#include "util/type_traits.hpp"

namespace cp {

namespace internal {

template <class T> struct hash {};

template <class T> requires internal::is_integral_v<T>
struct hash<T> {
  unsigned long long operator()(const T& x) const {
    static const unsigned long long fixed_random = seed_gen();
    unsigned long long h = (unsigned long long)(x);
    h += fixed_random;
    h = (h ^ (h >> 30)) * 0xbf58476d1ce4e5b9;
    h = (h ^ (h >> 27)) * 0x94d049bb133111eb;;
    return h ^ (h >> 31);
  }
};

template <class T> void hash_combine(unsigned long long& seed, const T& val) {
  static const unsigned long long fixed_random = seed_gen();
  seed += fixed_random;
  seed ^= hash<T>()(val);
  seed = (seed ^ (seed >> 30)) * 0xbf58476d1ce4e5b9;
  seed = (seed ^ (seed >> 27)) * 0x94d049bb133111eb;;
}

// string

template <> struct hash<std::string> {
  unsigned long long operator()(const std::string& s) const {
    unsigned long long hs = 0;
    for (auto& c : s) internal::hash_combine(hs, c);
    return hs;
  }
};

// tuple_like (array, pair, tuple)

template <class Tuple> requires internal::is_tuple_like_v<Tuple>
struct hash<Tuple> {
  unsigned long long operator()(const Tuple& t) const {
    unsigned long long hs = 0;
    [&]<size_t... I>(std::index_sequence<I...>) {
      (internal::hash_combine(hs, std::get<I>(t)), ...);
    }(std::make_index_sequence<std::tuple_size_v<Tuple>>());
    return hs;
  }
};

// vector

template <class T, class Alloc> struct hash<std::vector<T, Alloc>> {
  unsigned long long operator()(const std::vector<T, Alloc>& v) const {
    unsigned long long hs = 0;
    for (const auto& x : v) internal::hash_combine(hs, x);
    return hs;
  }
};

} // namespace internal

} // namespace cp