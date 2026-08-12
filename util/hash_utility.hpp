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

template <class T> requires (is_integral_v<T> && !(is_signed_int128_v<T> || is_unsigned_int128_v<T>))
struct hash<T> {
  unsigned long long operator()(const T& x) const {
    static const unsigned long long fixed_random = mt64();
    unsigned long long hs = (unsigned long long)(x);
    hs += fixed_random;
    hs = (hs ^ (hs >> 30)) * 0xbf58476d1ce4e5b9;
    hs = (hs ^ (hs >> 27)) * 0x94d049bb133111eb;;
    return hs ^ (hs >> 31);
  }
};

template <class T> void hash_combine(unsigned long long& seed, const T& val) {
  static const unsigned long long fixed_random = mt64();
  seed += fixed_random;
  seed ^= hash<T>()(val);
  seed = (seed ^ (seed >> 30)) * 0xbf58476d1ce4e5b9;
}

template <> struct hash<__int128> {
  unsigned long long operator()(const __int128& x) const {
    unsigned long long hs = 0;
    hash_combine(hs, (unsigned long long)((unsigned __int128)(x) >> 64));
    hash_combine(hs, (unsigned long long)(x));
    return hs;
  }
};

template <> struct hash<unsigned __int128> {
  unsigned long long operator()(const unsigned __int128& x) const {
    unsigned long long hs = 0;
    hash_combine(hs, (unsigned long long)(x >> 64));
    hash_combine(hs, (unsigned long long)(x));
    return hs;
  }
};

// string

template <> struct hash<std::string> {
  unsigned long long operator()(const std::string& s) const {
    unsigned long long hs = 0;
    for (auto& c : s) hash_combine(hs, c);
    return hs;
  }
};

// tuple_like (array, pair, tuple)

template <class Tuple> requires is_tuple_like_v<Tuple>
struct hash<Tuple> {
  unsigned long long operator()(const Tuple& t) const {
    unsigned long long hs = 0;
    [&]<size_t... I>(std::index_sequence<I...>) {
      (hash_combine(hs, std::get<I>(t)), ...);
    }(std::make_index_sequence<std::tuple_size_v<Tuple>>());
    return hs;
  }
};

// vector

template <class T, class Alloc> struct hash<std::vector<T, Alloc>> {
  unsigned long long operator()(const std::vector<T, Alloc>& v) const {
    unsigned long long hs = 0;
    for (const auto& x : v) hash_combine(hs, x);
    return hs;
  }
};

} // namespace internal

} // namespace cp