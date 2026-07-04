#pragma once

#include <algorithm>
#include <array>
#include <random>
#include <type_traits>

#include "random/rng.hpp"

namespace cp {

struct hash61 {
public:
  static hash61 get_base() {
    hash61 hs;
    for (int i = 0; i < num_of_base; i++) {
      do {
        hs.v[i] = mt64() % m;
      } while (!is_primitive(hs.v[i]));
    }
    return hs;
  }

  hash61() {}
  template <class T, std::enable_if_t<std::is_signed_v<T>>* = nullptr>
  hash61(T _v) {
    long long x = (long long)(_v % m);
    if (x < 0) x += m;
    std::fill(v.begin(), v.end(), x);
  }
  template <class T, std::enable_if_t<std::is_unsigned_v<T>>* = nullptr>
  hash61(T _v) {
    std::fill(v.begin(), v.end(), (long long)(_v % m));
  }

  hash61& operator+=(const hash61& rhs) {
    for (int i = 0; i < num_of_base; i++) {
      v[i] += rhs.v[i];
      if (v[i] >= m) v[i] -= m;
    }
    return *this;
  }
  hash61& operator-=(const hash61& rhs) {
    for (int i = 0; i < num_of_base; i++) {
      v[i] += m - rhs.v[i];
      if (v[i] >= m) v[i] -= m;
    }
    return *this;
  }
  hash61& operator*=(const hash61& rhs) {
    for (int i = 0; i < num_of_base; i++) {
      v[i] = mul(v[i], rhs.v[i]);
    }
    return *this;
  }

  hash61 operator+() const { return *this; }
  hash61 operator-() const { return hash61() - *this; }

  friend hash61 operator+(const hash61& lhs, const hash61& rhs) { return hash61(lhs) += rhs; }
  friend hash61 operator-(const hash61& lhs, const hash61& rhs) { return hash61(lhs) -= rhs; }
  friend hash61 operator*(const hash61& lhs, const hash61& rhs) { return hash61(lhs) *= rhs; }

  friend bool operator==(const hash61& lhs, const hash61& rhs) { return lhs.v == rhs.v; }
  friend bool operator!=(const hash61& lhs, const hash61& rhs) { return lhs.v != rhs.v; }
  friend bool operator<(const hash61& lhs, const hash61& rhs) { return lhs.v < rhs.v; }
  friend bool operator>(const hash61& lhs, const hash61& rhs) { return lhs.v > rhs.v; }
  friend bool operator<=(const hash61& lhs, const hash61& rhs) { return lhs.v <= rhs.v; }
  friend bool operator>=(const hash61& lhs, const hash61& rhs) { return lhs.v >= rhs.v; }

private:
  static constexpr long long m = (1LL << 61) - 1;
  static constexpr int num_of_base = 2;
  std::array<long long, num_of_base> v;

  static long long pow(long long x, long long n) {
    long long r = 1;
    while (n) {
      if (n & 1) r = mul(r, x);
      x = mul(x, x);
      n >>= 1;
    }
    return r;
  }

  static bool is_primitive(long long x) {
    for (long long d : {2, 3, 5, 7, 11, 13, 31, 41, 61, 151, 331, 1321}) {
      if (pow(x, (m - 1) / d) <= 1) return false;
    }
    return true;
  }

  static constexpr long long mul(long long a, long long b) {
    __int128 r = a;
    r *= b;
    r = (r >> 61) + (r & m);
    if (r >= m) r -= m;
    return r;
  }
};

} // namespace cp