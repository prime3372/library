#pragma once

#include <cassert>
#include <cmath>

namespace cp {

template <class T>
constexpr long long ipow(long long x, T n) {
  assert(0 <= n);
  long long r = 1;
  while (n) {
    if (n & 1) r *= x;
    x *= x;
    n >>= 1;
  }
  return r;
}

template <class T>
constexpr __int128 ipow128(__int128 x, T n) {
  assert(0 <= n);
  __int128 r = 1;
  while (n) {
    if (n & 1) r *= x;
    x *= x;
    n >>= 1;
  }
  return r;
}

template <class T>
constexpr T isqrt(T x) {
  T y = T(std::sqrt(x));
  while (y && y > x / y) y--;
  while ((y + 1) <= x / (y + 1)) y++;
  return y;
}

template <class T>
constexpr T icbrt(T x) {
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