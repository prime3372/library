#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <type_traits>

#include "random/base.hpp"
#include "util/type_traits.hpp"

namespace cp {

class hash61 {
  using ull = unsigned long long;

 public:
  static hash61 get_basis() {
    hash61 hs;
    do {
      hs.v = uniform(1ULL, m - 1);
    } while (!is_primitive(hs.v));
    return hs;
  }
  static hash61 get_rand() { return hash61(uniform(1ULL, m - 1)); }

  hash61() : v(0) {}
  template <class T> requires internal::is_signed_int_v<T>
  hash61(T _v) {
    long long x = (long long)(_v % m);
    if (x < 0) x += m;
    v = x;
  }
  template <class T> requires internal::is_unsigned_int_v<T>
  hash61(T _v) {
    v = (ull)(_v % m);
  }

  ull val() const { return v; }

  hash61& operator++() {
    v++;
    if (v == m) v = 0;
    return *this;
  }
  hash61& operator--() {
    if (v == 0) v = m;
    v--;
    return *this;
  }
  hash61 operator++(int) {
    hash61 res = *this;
    ++*this;
    return res;
  }
  hash61 operator--(int) {
    hash61 res = *this;
    --*this;
    return res;
  }

  hash61& operator+=(const hash61& rhs) {
    v += rhs.v;
    if (v >= m) v -= m;
    return *this;
  }
  hash61& operator-=(const hash61& rhs) {
    v += m - rhs.v;
    if (v >= m) v -= m;
    return *this;
  }
  hash61& operator*=(const hash61& rhs) {
    v = mul(v, rhs.v);
    return *this;
  }
  hash61& operator/=(const hash61& rhs) { return *this = *this * rhs.inv(); }

  hash61 operator+() const { return *this; }
  hash61 operator-() const { return hash61() - *this; }

  friend hash61 operator+(const hash61& lhs, const hash61& rhs) {
    return hash61(lhs) += rhs;
  }
  friend hash61 operator-(const hash61& lhs, const hash61& rhs) {
    return hash61(lhs) -= rhs;
  }
  friend hash61 operator*(const hash61& lhs, const hash61& rhs) {
    return hash61(lhs) *= rhs;
  }

  friend bool operator==(const hash61& lhs, const hash61& rhs) {
    return lhs.v == rhs.v;
  }
  friend bool operator!=(const hash61& lhs, const hash61& rhs) {
    return lhs.v != rhs.v;
  }
  friend bool operator<(const hash61& lhs, const hash61& rhs) {
    return lhs.v < rhs.v;
  }
  friend bool operator>(const hash61& lhs, const hash61& rhs) {
    return lhs.v > rhs.v;
  }
  friend bool operator<=(const hash61& lhs, const hash61& rhs) {
    return lhs.v <= rhs.v;
  }
  friend bool operator>=(const hash61& lhs, const hash61& rhs) {
    return lhs.v >= rhs.v;
  }

  hash61 pow(long long k) const {
    assert(0 <= k);
    hash61 x = *this, r = 1;
    while (k) {
      if (k & 1) r *= x;
      x *= x;
      k >>= 1;
    }
    return r;
  }
  hash61 inv() const {
    assert(v);
    return pow(m - 2);
  }

  friend std::istream& operator>>(std::istream& is, hash61& hs) {
    long long t;
    is >> t;
    hs = t;
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, const hash61& hs) {
    return os << hs.v;
  }

 private:
  static constexpr ull m = (1LL << 61) - 1;
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