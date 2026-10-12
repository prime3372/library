#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <type_traits>

#include "random/engine.hpp"
#include "util/type-traits.hpp"

namespace cp {

class Hash61 {
  using ull = unsigned long long;

 public:
  static Hash61 get_basis() {
    Hash61 hs;
    do {
      hs.v = uniform(2ULL, m - 1);
    } while (!is_primitive(hs.v));
    return hs;
  }
  static Hash61 get_rand() { return Hash61(uniform(0ULL, m - 1)); }

  Hash61() : v(0) {}
  template <class T> requires(internal::is_signed_int_v<T>)
  Hash61(T _v) {
    long long x = (long long)(_v % m);
    if (x < 0) x += m;
    v = x;
  }
  template <class T> requires(internal::is_unsigned_int_v<T>)
  Hash61(T _v) {
    v = (ull)(_v % m);
  }

  ull val() const { return v; }

  Hash61& operator++() {
    v++;
    if (v == m) v = 0;
    return *this;
  }
  Hash61& operator--() {
    if (v == 0) v = m;
    v--;
    return *this;
  }
  Hash61 operator++(int) {
    Hash61 res = *this;
    ++*this;
    return res;
  }
  Hash61 operator--(int) {
    Hash61 res = *this;
    --*this;
    return res;
  }

  Hash61& operator+=(const Hash61& rhs) {
    v += rhs.v;
    if (v >= m) v -= m;
    return *this;
  }
  Hash61& operator-=(const Hash61& rhs) {
    v += m - rhs.v;
    if (v >= m) v -= m;
    return *this;
  }
  Hash61& operator*=(const Hash61& rhs) {
    v = mul(v, rhs.v);
    return *this;
  }
  Hash61& operator/=(const Hash61& rhs) { return *this = *this * rhs.inv(); }

  Hash61 operator+() const { return *this; }
  Hash61 operator-() const { return Hash61() - *this; }

  friend Hash61 operator+(const Hash61& lhs, const Hash61& rhs) {
    return Hash61(lhs) += rhs;
  }
  friend Hash61 operator-(const Hash61& lhs, const Hash61& rhs) {
    return Hash61(lhs) -= rhs;
  }
  friend Hash61 operator*(const Hash61& lhs, const Hash61& rhs) {
    return Hash61(lhs) *= rhs;
  }

  friend bool operator==(const Hash61& lhs, const Hash61& rhs) {
    return lhs.v == rhs.v;
  }
  friend bool operator!=(const Hash61& lhs, const Hash61& rhs) {
    return lhs.v != rhs.v;
  }
  friend bool operator<(const Hash61& lhs, const Hash61& rhs) {
    return lhs.v < rhs.v;
  }
  friend bool operator>(const Hash61& lhs, const Hash61& rhs) {
    return lhs.v > rhs.v;
  }
  friend bool operator<=(const Hash61& lhs, const Hash61& rhs) {
    return lhs.v <= rhs.v;
  }
  friend bool operator>=(const Hash61& lhs, const Hash61& rhs) {
    return lhs.v >= rhs.v;
  }

  Hash61 pow(long long k) const {
    assert(0 <= k);
    Hash61 x = *this, r = 1;
    while (k) {
      if (k & 1) r *= x;
      x *= x;
      k >>= 1;
    }
    return r;
  }
  Hash61 inv() const {
    assert(v);
    return pow(m - 2);
  }

  friend std::istream& operator>>(std::istream& is, Hash61& hs) {
    long long t;
    is >> t;
    hs = t;
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, const Hash61& hs) {
    return os << hs.v;
  }

 private:
  static constexpr ull m = (1ULL << 61) - 1;
  ull v;

  static ull pow(ull x, ull n) {
    ull r = 1;
    while (n) {
      if (n & 1) r = mul(r, x);
      x = mul(x, x);
      n >>= 1;
    }
    return r;
  }

  static bool is_primitive(ull x) {
    constexpr ull divs[] = {2, 3, 5, 7, 11, 13, 31, 41, 61, 151, 331, 1321};
    for (ull d : divs) {
      if (pow(x, (m - 1) / d) <= 1) return false;
    }
    return true;
  }

  static ull mul(ull a, ull b) {
    unsigned __int128 r = a;
    r *= b;
    r = (r >> 61) + (r & m);
    if (r >= m) r -= m;
    return (ull)(r);
  }
};

}  // namespace cp