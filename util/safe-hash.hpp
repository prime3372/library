#pragma once

#include <ranges>
#include <tuple>
#include <utility>
#include <vector>

#include "random/engine.hpp"
#include "util/type-traits.hpp"

namespace cp {

template <class> struct SafeHash {};

template <class T> void hash_combine(unsigned long long& seed, const T& val) {
  seed ^= SafeHash<T>()(val) + (seed << 6) + (seed >> 2) + 0x9e3779b9ULL;
}

template <> struct SafeHash<unsigned long long> {
  unsigned long long operator()(unsigned long long x) const {
    static const unsigned long long fixed_rand = rng();
    x += fixed_rand;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
  }
};

template <class T>
  requires(internal::is_integral_v<T> && !internal::is_128bit_int_v<T>)
struct SafeHash<T> {
  unsigned long long operator()(T x) const {
    return SafeHash<unsigned long long>()(x);
  }
};

template <class T>
  requires(internal::is_128bit_int_v<T>)
struct SafeHash<T> {
  unsigned long long operator()(T x) const {
    using ull = unsigned long long;
    unsigned __int128 ux = x;
    if ((ux >> 64) == 0) return SafeHash<ull>()(ull(ux));
    ull hs = 0;
    hash_combine(hs, ull(ux));
    hash_combine(hs, ull(ux >> 64));
    return hs;
  }
};

template <class T>
  requires(internal::is_modint_v<T>)
struct SafeHash<T> {
  unsigned long long operator()(const T& x) const {
    return SafeHash<int>()(x.val());
  }
};

template <class Range>
  requires(std::ranges::range<Range>)
struct SafeHash<Range> {
  unsigned long long operator()(const Range& r) const {
    unsigned long long hs = 0;
    for (const auto& x : r) hash_combine(hs, x);
    return hs;
  }
};

template <class T, class U> struct SafeHash<std::pair<T, U>> {
  unsigned long long operator()(const std::pair<T, U>& p) const {
    unsigned long long hs = 0;
    hash_combine(hs, p.first);
    hash_combine(hs, p.second);
    return hs;
  }
};

template <class... Args> struct SafeHash<std::tuple<Args...>> {
  unsigned long long operator()(const std::tuple<Args...>& t) const {
    unsigned long long hs = 0;
    std::apply([&](const auto&... args) { (hash_combine(hs, args), ...); }, t);
    return hs;
  }
};

}  // namespace cp