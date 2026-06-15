#pragma once

#include <cassert>
#include <cmath>
#include <concepts>
#include <type_traits>
#include <utility>

template <std::integral T, std::integral U>
constexpr std::common_type_t<T, U> quot(T a, U b) { return a < 0 ? (a + 1) / b - 1 : a / b; };

template <std::integral T, std::integral U>
constexpr std::common_type_t<T, U> rem(T a, U b) { return a - quot(a, b) * b; };

template <std::integral T, std::integral U>
constexpr std::common_type_t<T, long long> ipow(T x, U n) {
  assert(0 <= n);
  std::common_type_t<T, long long> r = 1, t = x;
  while (n) {
    if (n & 1) r *= t;
    t *= t;
    n >>= 1;
  }
  return r;
}

template <std::integral T>
constexpr std::common_type_t<T, long long> isqrt(T x) {
  using U = std::common_type_t<T, long long>;
  U y = U(std::sqrt(x));
  while (y && y > x / y) y--;
  while ((y + 1) <= x / (y + 1)) y++;
  return y;
}

template <std::integral T>
constexpr std::common_type_t<T, long long> icbrt(T x) {
  using U = std::common_type_t<T, long long>;
  U y = U(std::cbrt(x));
  while (y && y * y > x / y) y--;
  while ((y + 1) * (y + 1) <= x / (y + 1)) y++;
  return y;
}

constexpr unsigned long long kth_root(unsigned long long x,
                                      unsigned long long k) {
  assert(k);
  if (x <= 1 || k == 1) return x;
  if (64 <= k) return 1;
  auto check = [&](unsigned __int128 y) {
    unsigned __int128 z = 1;
    for (int e = k; e; e >>= 1) {
      if (e & 1) z *= y;
      y *= y;
    }
    return z <= x;
  };
  unsigned long long y = (unsigned long long)std::pow(x, 1.0 / k);
  while (!check(y)) y--;
  while (check(y + 1)) y++;
  return y;
}

constexpr long long pow_mod(long long x, long long n, long long m) {
  assert(0 <= n && 1 <= m);
  __int128 r = 1, y = x < 0 ? x % m + m : x % m;
  while (n) {
    if (n & 1) r = r * y % m;
    y = y * y % m;
    n >>= 1;
  }
  return (long long)r;
}

constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
  assert(1 <= b);
  a = a < 0 ? a % b + b : a % b;
  long long g0 = b, g1 = a;
  long long x0 = 0, x1 = 1;
  while (g1) {
    long long q = g0 / g1;
    g0 -= g1 * q;
    x0 -= x1 * q;
    std::swap(g0, g1);
    std::swap(x0, x1);
  }
  if (x0 < 0) x0 += b / g0;
  return {g0, x0};
}

constexpr long long inv_mod(long long x, long long m) {
  assert(2 <= m);
  auto z = inv_gcd(x, m);
  assert(z.first == 1);
  return z.second;
}
