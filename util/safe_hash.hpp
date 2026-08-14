#pragma once

#include <array>
#include <cstddef>
#include <functional>
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
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
  x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
  return x ^ (x >> 31);
}

template <class T> void hash_combine(unsigned long long& seed, const T& val) {
  seed ^= safe_hash<T>()(val) + (seed << 6) + (seed >> 2) + 0x9e3779b9ULL;
}

} // namespace internal

template <class T> requires internal::is_integral_v<T> && (sizeof(T) <= 8)
struct safe_hash<T> {
  unsigned long long operator()(const T& x) const {
    return internal::splitmix64((unsigned long long)(x));
  }
};

template <class T>
  requires internal::is_signed_int128_v<T> || internal::is_unsigned_int128_v<T>
struct safe_hash<T> {
  unsigned long long operator()(const T& x) const {
    unsigned __int128 ux = x;
    if ((ux >> 64) == 0) {
      return safe_hash<unsigned long long>()((unsigned long long)(ux));
    }
    unsigned long long hs = 0;
    internal::hash_combine(hs, (unsigned long long)(ux >> 64));
    internal::hash_combine(hs, (unsigned long long)(ux));
    return hs;
  }
};

template <class T> requires std::is_floating_point_v<T>
struct safe_hash<T> {
  unsigned long long operator()(const T& x) const {
    return internal::splitmix64(std::hash<T>()(x));
  }
};

template <class T, size_t Size>
struct safe_hash<std::array<T, Size>> {
  unsigned long long operator()(const std::array<T, Size>& a) const {
    unsigned long long hs = 0;
    for (const auto& x : a) internal::hash_combine(hs, x);
    return hs;
  }
};

template <class T, class U>
struct safe_hash<std::pair<T, U>> {
  unsigned long long operator()(const std::pair<T, U>& p) const {
    unsigned long long hs = 0;
    internal::hash_combine(hs, p.first);
    internal::hash_combine(hs, p.second);
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