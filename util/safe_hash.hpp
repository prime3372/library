#pragma once

#include <array>
#include <deque>
#include <cstddef>
#include <functional>
#include <string>
#include <tuple>
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

template <class T> requires internal::is_modint_v<T>
struct safe_hash<T> {
  unsigned long long operator()(const T& x) const {
    return safe_hash<int>()(x.val());
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

template <class T, class Alloc>
struct safe_hash<std::deque<T, Alloc>> {
  unsigned long long operator()(const std::deque<T, Alloc>& dq) const {
    unsigned long long hs = 0;
    for (const auto& x : dq) internal::hash_combine(hs, x);
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

template <> struct safe_hash<std::string> {
  unsigned long long operator()(const std::string& s) const {
    unsigned long long hs = 0;
    for (char c : s) internal::hash_combine(hs, c);
    return hs;
  }
};

template <class... Args>
struct safe_hash<std::tuple<Args...>> {
  unsigned long long operator()(const std::tuple<Args...>& t) const {
    unsigned long long hs = 0;
    [&]<size_t... I>(std::index_sequence<I...>) {
      (internal::hash_combine(hs, get<I>(t)), ...);
    }(std::make_index_sequence<sizeof...(Args)>());
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