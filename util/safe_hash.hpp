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

template <class> struct safe_hash {};

namespace internal {

static unsigned long long splitmix64(unsigned long long x) {
  static const unsigned long long fixed_rand = mt64();
  x += fixed_rand;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}

template <class T> void hash_combine(unsigned long long& seed, const T& val) {
  seed = internal::splitmix64(seed) ^ (safe_hash<T>()(val) + (seed << 6) + (seed >> 2) + 0x9e3779b9);
}

} // namespace internal

template <class T> requires internal::is_integral_v<T> && (sizeof(T) <= 8)
struct safe_hash<T> {
  unsigned long long operator()(const T& x) const {
    return internal::splitmix64((unsigned long long)(x));
  }
};

template <class T> requires internal::is_signed_int128_v<T> || internal::is_unsigned_int128_v<T>
struct safe_hash<T> {
  unsigned long long operator()(const T& x) const {
    if ((x >> 64) == 0) {
      return safe_hash<unsigned long long>()((unsigned long long)(x));
    }
    unsigned long long hs = 0;
    internal::hash_combine(hs, (unsigned long long)((unsigned __int128)(x) >> 64));
    internal::hash_combine(hs, (unsigned long long)(x));
    return hs;
  }
};

template <> struct safe_hash<std::string> {
  unsigned long long operator()(const std::string& s) const {
    unsigned long long hs = 0;
    for (auto& c : s) internal::hash_combine(hs, c);
    return hs;
  }
};

template <class Tuple> requires internal::is_tuple_like_v<Tuple>
struct safe_hash<Tuple> {
  unsigned long long operator()(const Tuple& t) const {
    unsigned long long hs = 0;
    [&]<size_t... I>(std::index_sequence<I...>) {
      (internal::hash_combine(hs, std::get<I>(t)), ...);
    }(std::make_index_sequence<std::tuple_size_v<Tuple>>());
    return hs;
  }
};

template <class T, class Alloc>
struct safe_hash<std::vector<T, Alloc>> {
  unsigned long long operator()(const std::vector<T, Alloc>& v) const {
    unsigned long long hs = 0;
    for (const auto& x : v) internal::hash_combine(hs, x);
    return hs;
  }
};

} // namespace cp