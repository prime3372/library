#pragma once

#include <cassert>
#include <iostream>
#include <utility>
#include <type_traits>

#include "../number/barrett.hpp"
#include "../number/ext_gcd.hpp"
#include "type_traits.hpp"

namespace cp {

template <int id> struct dynamic_modint {
  using mint = dynamic_modint;

public:
  static void set_mod(int m) {
    assert(1 <= m);
    bt = barrett(m);
  }
  static int mod() { return bt.umod(); }

  dynamic_modint() : v(0) {}
  template <class T> requires std::is_signed_v<T>
  dynamic_modint(T _v) {
    long long x = (long long)(_v % (long long)(mod()));
    if (x < 0) x += mod();
    v = (unsigned int)(x);
  }
  template <class T> requires std::is_unsigned_v<T>
  dynamic_modint(T _v) {
    v = (unsigned int)(_v % mod());
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
    v += mod() - rhs.v;
    if (v >= umod()) v -= umod();
    return *this;
  }
  mint& operator*=(const mint& rhs) {
    v = bt.mul(v, rhs.v);
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
    auto eg = ext_gcd(v, mod());
    assert(eg.first == 1);
    return eg.second;
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
  inline static barrett bt = barrett(998244353);
  static unsigned int umod() { return bt.umod(); }
};

using modint = dynamic_modint<-1>;

template <int id>
struct is_modint<dynamic_modint<id>> : std::true_type {};
template <int id>
struct is_dynamic_modint<dynamic_modint<id>> : std::true_type {};

} // namespace cp