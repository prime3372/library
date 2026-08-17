#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "poly/convolution_ll.hpp"
#include "util/io_utility.hpp"

namespace cp {

class formal_power_series_ll {
  using fps = formal_power_series_ll;
  using ll = long long;

 public:
  formal_power_series_ll() {}
  explicit formal_power_series_ll(int n) : a(n) {}
  explicit formal_power_series_ll(int n, ll val) : a(n, val) {}
  explicit formal_power_series_ll(const std::vector<ll>& _a) : a(_a) {}

  ll& operator[](int i) {
    assert(0 <= i && i < size());
    return a[i];
  }
  const ll& operator[](int i) const {
    assert(0 <= i && i < size());
    return a[i];
  }

  fps& operator+=(ll rhs) {
    return *this += fps(1, rhs);
  }
  fps& operator+=(const fps& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) a[i] += rhs[i];
    return *this;
  }

  fps& operator-=(ll rhs) {
    return *this -= fps(1, rhs);
  }
  fps& operator-=(const fps& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) a[i] -= rhs[i];
    return *this;
  }

  fps& operator*=(ll rhs) {
    for (int i = 0; i < size(); i++) a[i] *= rhs;
    return *this;
  }
  fps& operator*=(const fps& rhs) {
    a = convolution_ll(a, rhs.a);
    return *this;
  }

  fps& operator/=(ll rhs) {
    for (int i = 0; i < size(); i++) a[i] /= rhs;
    return *this;
  }

  fps operator+() const { return *this; }
  fps operator-() const { return fps() - *this; }

  friend fps operator+(const fps& lhs, ll rhs) {
    return fps(lhs) += rhs;
  }
  friend fps operator+(ll lhs, const fps& rhs) {
    return fps(rhs) += lhs;
  }
  friend fps operator+(const fps& lhs, const fps& rhs) {
    return fps(lhs) += rhs;
  }
  friend fps operator-(const fps& lhs, ll rhs) {
    return fps(lhs) -= rhs;
  }
  friend fps operator-(ll lhs, const fps& rhs) {
    return fps(1, lhs) -= rhs;
  }
  friend fps operator-(const fps& lhs, const fps& rhs) {
    return fps(lhs) -= rhs;
  }
  friend fps operator*(const fps& lhs, ll rhs) {
    return fps(lhs) *= rhs;
  }
  friend fps operator*(ll lhs, const fps& rhs) {
    return fps(rhs) *= lhs;
  }
  friend fps operator*(const fps& lhs, const fps& rhs) {
    return fps(lhs) *= rhs;
  }
  friend fps operator/(const fps& lhs, ll rhs) {
    return fps(lhs) /= rhs;
  }
  friend fps operator/(ll lhs, const fps& rhs) {
    return fps(rhs) /= lhs;
  }

  int size() const { return int(a.size()); }
  bool empty() const { return a.empty(); }
  void resize(int n) { a.resize(n); }

  void swap(fps& other) { a.swap(other.a); }
  void clear() { a.clear(); }

  friend std::ostream& operator<<(std::ostream& os, const fps& rhs) {
    for (int i = 0; i < rhs.size(); i++) {
      os << rhs.a[i];
      if (i != rhs.size() - 1) os << " ";
    }
    return os;
  }

 private:
  std::vector<ll> a;
};

} // namespace cp