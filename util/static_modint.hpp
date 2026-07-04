#pragma once

#include <cassert>
#include <iostream>
#include <type_traits>

#include "../number/ext_gcd.hpp"
#include "../number/is_prime.hpp"
#include "type_traits.hpp"

namespace cp {

template <int m> requires (1 <= m) struct static_modint {
  using mint = static_modint;

public:
  static constexpr int mod() { return m; }

  static_modint() : v(0) {}
  template <class T> requires std::is_signed_v<T>
  static_modint(T _v) {
    long long x = (long long)(_v % (long long)(umod()));
    if (x < 0) x += umod();
    v = (unsigned int)(x);
  }
  template <class T> requires std::is_unsigned_v<T>
  static_modint(T _v) {
    v = (unsigned int)(_v % umod());
  }

  int val() const { return v; }

  mint& operator++() {
    v++;
    if (v == umod()) v = 0;
    return *this;
  }
  mint& operator--() {
    if (v == 0) v = umod();
    v--;
    return *this;
  }
  mint operator++(int) {
    mint res = *this;
    ++*this;
    return res;
  }
  mint operator--(int) {
    mint res = *this;
    --*this;
    return res;
  }

  mint& operator+=(const mint& rhs) {
    v += rhs.v;
    if (v >= umod()) v -= umod();
    return *this;
  }
  mint& operator-=(const mint& rhs) {
    v -= rhs.v;
    if (v >= umod()) v += umod();
    return *this;
  }
  mint& operator*=(const mint& rhs) {
    unsigned long long z = v;
    z *= rhs.v;
    v = (unsigned int)(z % umod());
    return *this;
  }
  mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }

  mint operator+() const { return *this; }
  mint operator-() const { return mint() - *this; }

  mint pow(long long n) const {
    assert(0 <= n);
    mint x = *this, r = 1;
    while (n) {
      if (n & 1) r *= x;
      x *= x;
      n >>= 1;
    }
    return r;
  }
  mint inv() const {
    if constexpr (prime) {
      assert(v);
      return pow(umod() - 2);
    } else {
      auto eg = ext_gcd(v, m);
      assert(eg.first == 1);
      return eg.second;
    }
  }

  friend mint operator+(const mint& lhs, const mint& rhs) { return mint(lhs) += rhs; }
  friend mint operator-(const mint& lhs, const mint& rhs) { return mint(lhs) -= rhs; }
  friend mint operator*(const mint& lhs, const mint& rhs) { return mint(lhs) *= rhs; }
  friend mint operator/(const mint& lhs, const mint& rhs) { return mint(lhs) /= rhs; }

  friend bool operator==(const mint& lhs, const mint& rhs) { return lhs.v == rhs.v; }
  friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs.v != rhs.v; }
  friend bool operator<(const mint& lhs, const mint& rhs) { return lhs.v < rhs.v; }
  friend bool operator>(const mint& lhs, const mint& rhs) { return lhs.v > rhs.v; }
  friend bool operator<=(const mint& lhs, const mint& rhs) { return lhs.v <= rhs.v; }
  friend bool operator>=(const mint& lhs, const mint& rhs) { return lhs.v >= rhs.v; }

  friend std::istream& operator>>(std::istream& is, mint& x) {
    long long t;
    is >> t;
    x = t;
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, const mint& x) {
    return os << x.v;
  }

private:
  unsigned int v;
  static constexpr unsigned int umod() { return m; }
  static constexpr bool prime = is_prime(m);
};

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;

template <int m>
struct is_modint<static_modint<m>> : public std::true_type {};
template <int m>
struct is_static_modint<static_modint<m>> : public std::true_type {};

} // namespace cp