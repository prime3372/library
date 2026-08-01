#pragma once

#include <cassert>
#include <cmath>

#include "util/type_traits.hpp"

namespace cp {

constexpr long long ipow(long long x, long long n) {
  assert(0 <= n);
  unsigned long long r = 1;
  while (n) {
    if (n & 1) r *= x;
    x *= (unsigned long long)(x);
    n >>= 1;
  }
  return r;
}

template <class T> requires internal::is_integral_v<T>
constexpr T isqrt(T x) {
  assert(0 <= x);
  T y = T(std::sqrt(double(x)));
  if constexpr (sizeof(T) > 8U) {
    if (y) y = (y + x / y) / 2; // Newton's method
  }
  while (y && y > x / y) y--;
  while ((y + 1) <= x / (y + 1)) y++;
  return y;
}

template <class T> requires internal::is_integral_v<T>
constexpr T icbrt(T x) {
  assert(0 <= x);
  T y = T(std::cbrt(double(x)));
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