#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>

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

unsigned long long isqrt(unsigned long long x) {
  unsigned long long y = (unsigned long long)(std::sqrt(double(x)));
  while (y != 0 && y > x / y) y--;
  while ((y + 1) <= x / (y + 1)) y++;
  return y;
}

unsigned long long icbrt(unsigned long long x) {
  unsigned long long y = (unsigned long long)(std::cbrt(double(x)));
  while (y != 0 && y * y > x / y) y--;
  while ((y + 1) * (y + 1) <= x / (y + 1)) y++;
  return y;
}

template <class T> int sign(T x) { return x < 0 ? -1 : x == 0 ? 0 : 1; }

long long floor(long long n, long long d) {
  assert(d != 0);
  if (d < 0) {
    n = -n;
    d = -d;
  }
  if (n < 0) return (n + 1) / d - 1;
  return n / d;
}

long long ceil(long long n, long long d) { return floor(n - sign(d), d) + 1; }

long long mod(long long n, long long m) { return n - floor(n, m) * m; }

}  // namespace cp