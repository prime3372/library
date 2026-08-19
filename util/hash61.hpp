#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <type_traits>

#include "random/base.hpp"
#include "util/safe_hash.hpp"
#include "util/type_traits.hpp"

namespace cp {

class hash61 {
 public:
  static hash61 get_basis() {
    hash61 hs;
    do { hs.v = uniform(1ULL, m - 1); } while (!is_primitive(hs.v));
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
    v = (unsigned long long)(_v % m);
  }

  unsigned long long val() const { return v; }

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
  static constexpr unsigned long long m = (1LL << 61) - 1;
  unsigned long long v;

  static unsigned long long pow(unsigned long long x, unsigned long long n) {
    unsigned long long r = 1;
    while (n) {
      if (n & 1) r = mul(r, x);
      x = mul(x, x);
      n >>= 1;
    }
    return r;
  }

  static bool is_primitive(unsigned long long x) {
    constexpr unsigned long long divs[] = {2,  3,  5,  7,   11,  13,
                                           31, 41, 61, 151, 331, 1321};
    for (unsigned long long d : divs) {
      if (pow(x, (m - 1) / d) <= 1) return false;
    }
    return true;
  }

  static unsigned long long mul(unsigned long long a, unsigned long long b) {
    unsigned __int128 r = a;
    r *= b;
    r = (r >> 61) + (r & m);
    if (r >= m) r -= m;
    return (unsigned long long)(r);
  }
};

template <> struct safe_hash<hash61> {
  unsigned long long operator()(const hash61& hs) const {
    return safe_hash<unsigned long long>()(hs.val());
  }
};

}  // namespace cp