#pragma once

#include <cassert>
#include <cmath>

#include "util/type_traits.hpp"

namespace cp {

constexpr __int128 ipow(__int128 x, __int128 n) {
  assert(0 <= n);
  __int128 r = 1;
  while (n) {
    if (n & 1) r *= x;
    x *= x;
    n >>= 1;
  }
  return r;
}

template <internal::integral T>
constexpr T isqrt(T x) {
  assert(0 <= x);
  T y = T(std::sqrt(double(x)));
  if constexpr (sizeof(T) > 8) {
    y = (y + x / y) / 2;
    y = (y + x / y) / 2;
  }
  while (y && y > x / y) y--;
  while ((y + 1) <= x / (y + 1)) y++;
  return y;
}

template <internal::integral T>
constexpr T icbrt(T x) {
  assert(0 <= x);
  T y = T(std::cbrt(x));
  while (y && y * y > x / y) y--;
  while ((y + 1) * (y + 1) <= x / (y + 1)) y++;
  return y;
}

template <class T>
constexpr bool chmin(T& a, T b) {
  if (b < a) {
    a = b;
    return true;
  }
  return false;
}

template <class T>
constexpr bool chmax(T& a, T b) {
  if (b > a) {
    a = b;
    return true;
  }
  return false;
}

} // namespace cp