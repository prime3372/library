#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>

namespace cp {

template <class T = long long> T ipow(long long x, long long n) {
  assert(0 <= n);
  T r = 1, t = x;
  while (n) {
    if (n & 1) r *= t;
    t *= t;
    n >>= 1;
  }
  return r;
}

template <class T> T isqrt(T x) {
  T y = T(std::sqrt(double(x)));
  if (sizeof(T) > 8) {
    y = (y + x / y) / 2;  // Newton's method
  }
  while (y != 0 && y > x / y) y--;
  while ((y + 1) <= x / (y + 1)) y++;
  return y;
}

template <class T> T icbrt(T x) {
  T y = T(std::cbrt(double(x)));
  while (y != 0 && y * y > x / y) y--;
  while ((y + 1) * (y + 1) <= x / (y + 1)) y++;
  return y;
}

template <class T> int sign(T x) { return x < 0 ? -1 : x == 0 ? 0 : 1; }

template <class T, class U> T floor(T n, U d) {
  assert(d != 0);
  if (d < 0) {
    n = -n;
    d = -d;
  }
  if (n < 0) {
    return T((n + 1) / d - 1);
  } else {
    return T(n / d);
  }
}

template <class T, class U> T ceil(T n, U d) {
  return floor(n - sign(d), d) + 1;
}

template <class T, class U> U mod(T n, U m) { return U(n - floor(n, m) * m); }

}  // namespace cp