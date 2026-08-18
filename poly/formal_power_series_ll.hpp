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

 public:
  formal_power_series_ll() {}
  explicit formal_power_series_ll(int n) : a(n) {}
  explicit formal_power_series_ll(int n, long long val) : a(n, val) {}
  explicit formal_power_series_ll(const std::vector<long long>& _a) : a(_a) {}

  long long& operator[](int i) {
    assert(0 <= i && i < size());
    return a[i];
  }
  const long long& operator[](int i) const {
    assert(0 <= i && i < size());
    return a[i];
  }

  fps& operator+=(long long rhs) { return *this += fps(1, rhs); }
  fps& operator+=(const fps& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) a[i] += rhs[i];
    return *this;
  }

  fps& operator-=(long long rhs) { return *this -= fps(1, rhs); }
  fps& operator-=(const fps& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) a[i] -= rhs[i];
    return *this;
  }

  fps& operator*=(long long rhs) {
    for (int i = 0; i < size(); i++) a[i] *= rhs;
    return *this;
  }
  fps& operator*=(const fps& rhs) {
    a = convolution_ll(a, rhs.a);
    return *this;
  }

  fps& operator/=(long long rhs) {
    for (int i = 0; i < size(); i++) a[i] /= rhs;
    return *this;
  }

  fps operator+() const { return *this; }
  fps operator-() const { return fps() - *this; }

  friend fps operator+(const fps& lhs, long long rhs) {
    return fps(lhs) += rhs;
  }
  friend fps operator+(long long lhs, const fps& rhs) {
    return fps(rhs) += lhs;
  }
  friend fps operator+(const fps& lhs, const fps& rhs) {
    return fps(lhs) += rhs;
  }
  friend fps operator-(const fps& lhs, long long rhs) {
    return fps(lhs) -= rhs;
  }
  friend fps operator-(long long lhs, const fps& rhs) {
    return fps(1, lhs) -= rhs;
  }
  friend fps operator-(const fps& lhs, const fps& rhs) {
    return fps(lhs) -= rhs;
  }
  friend fps operator*(const fps& lhs, long long rhs) {
    return fps(lhs) *= rhs;
  }
  friend fps operator*(long long lhs, const fps& rhs) {
    return fps(rhs) *= lhs;
  }
  friend fps operator*(const fps& lhs, const fps& rhs) {
    return fps(lhs) *= rhs;
  }
  friend fps operator/(const fps& lhs, long long rhs) {
    return fps(lhs) /= rhs;
  }
  friend fps operator/(long long lhs, const fps& rhs) {
    return fps(rhs) /= lhs;
  }

  int size() const { return int(a.size()); }
  bool empty() const { return a.empty(); }
  void resize(int n) { a.resize(n); }

  void swap(fps& other) { a.swap(other.a); }
  void clear() { a.clear(); }

  friend std::istream& operator>>(std::istream& is, fps& rhs) {
    for (long long& x : rhs.a) is >> x;
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, const fps& rhs) {
    for (int i = 0; i < rhs.size(); i++) {
      os << rhs.a[i];
      if (i != rhs.size() - 1) os << " ";
    }
    return os;
  }

 private:
  std::vector<long long> a;
};

}  // namespace cp