#pragma once

#include <cassert>

namespace cp {

template <class T>
constexpr __int128 ipow(__int128 x, T n) {
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