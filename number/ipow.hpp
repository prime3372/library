#pragma once

#include <cassert>
#include <concepts>
#include <type_traits>

template <std::integral T, std::integral U>
constexpr std::common_type_t<T, U, long long> ipow(T x, U n) {
  assert(0 <= n);
  std::common_type_t<T, U, long long> r = 1, t = x;
  while (n) {
    if (n & 1) r *= t;
    t *= t;
    n >>= 1;
  }
  return r;
}
