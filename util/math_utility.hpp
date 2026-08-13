#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>

#include "util/type_traits.hpp"

namespace cp {

long long ipow(long long x, long long n) {
  assert(0 <= n);
  long long r = 1;
  while (n) {
    if (n & 1) r *= x;
    x *= x;
    n >>= 1;
  }
  return r;
}

__int128 ipow128(__int128 x, long long n) {
  assert(0 <= n);
  __int128 r = 1;
  while (n) {
    if (n & 1) r *= x;
    x *= x;
    n >>= 1;
  }
  return r;
}

template <class T> requires internal::is_integral_v<T>
T isqrt(T x) {
  assert(0 <= x);
  T y = T(std::sqrt(double(x)));
  if (sizeof(T) > 8ULL) {
    if (y) y = (y + x / y) / 2; // Newton's method
  }
  while (y && y > x / y) y--;
  while ((y + 1) <= x / (y + 1)) y++;
  return y;
}

template <class T> requires internal::is_integral_v<T>
T icbrt(T x) {
  assert(0 <= x);
  T y = T(std::cbrt(double(x)));
  while (y && y * y > x / y) y--;
  while ((y + 1) * (y + 1) <= x / (y + 1)) y++;
  return y;
}

template <class T> bool chmin(T& a, T b) {
  if (b < a) {
    a = b;
    return true;
  }
  return false;
}

template <class T> bool chmax(T& a, T b) {
  if (b > a) {
    a = b;
    return true;
  }
  return false;
}

template <class T> auto min(const T& a) {
  assert(!a.empty());
  return *std::min_element(a.begin(), a.end());
}

template <class T> auto max(const T& a) {
  assert(!a.empty());
  return *std::max_element(a.begin(), a.end());
}

template <class T> long long sum(const T& a) {
  return std::accumulate(a.begin(), a.end(), 0LL);
}

template <class T> void sort_unique(T& a) {
  std::sort(a.begin(), a.end());
  a.erase(std::unique(a.begin(), a.end()), a.end());
}

} // namespace cp