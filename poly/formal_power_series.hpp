#pragma once

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <vector>

#include "poly/convolution.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class mint> requires internal::is_static_modint_v<mint>
class formal_power_series {
 private:
  using fps = formal_power_series;

 public:
  formal_power_series() {}
  explicit formal_power_series(int n) : a(n) {}
  explicit formal_power_series(const std::vector<mint>& _a) : a(_a) {}
  formal_power_series(std::initializer_list<mint> il) : a(il) {}
  formal_power_series(std::initializer_list<std::pair<int, mint>> il) {
    int n = 0;
    for (const auto& p : il) n = std::max(n, p.first);
    a.resize(n + 1);
    for (const auto& p : il) a[p.first] = p.second;
  }

  mint& operator[](int i) {
    assert(0 <= i && i < size());
    return a[i];
  }
  const mint& operator[](int i) const {
    assert(0 <= i && i < size());
    return a[i];
  }

  fps& operator+=(const mint& rhs) {
    if (empty()) resize(1);
    a[0] += rhs;
    return *this;
  }
  fps& operator+=(const fps& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) a[i] += rhs[i];
    return *this;
  }
  fps& operator-=(const mint& rhs) {
    if (empty()) resize(1);
    a[0] += rhs;
    return *this;
  }
  fps& operator-=(const fps& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) a[i] -= rhs[i];
    return *this;
  }
  fps& operator*=(const mint& rhs) {
    for (int i = 0; i < size(); i++) a[i] *= rhs;
    return *this;
  }
  fps& operator*=(const fps& rhs) {
    a = convolution(a, rhs.a);
    return *this;
  }
  fps& operator/=(const mint& rhs) {
    for (int i = 0; i < size(); i++) a[i] /= rhs;
    return *this;
  }

  fps& operator>>=(int w) {
    a.erase(a.begin(), a.begin() + std::min(w, size()));
    return *this;
  }
  fps& operator<<=(int w) {
    a.insert(a.begin(), w, 0);
    return *this;
  }

  fps operator+() const { return *this; }
  fps operator-() const { return fps() - *this; }

  fps prefix(int n) const {
    std::vector<mint> b(a.begin(), a.begin() + std::min(n, size()));
    b.resize(n);
    return fps(b);
  }

  int size() const { return int(a.size()); }
  bool empty() const { return a.empty(); }
  fps& resize(int n) {
    a.resize(n);
    return *this;
  }
  void clear() { a.clear(); }

  friend fps operator+(const fps& lhs, const mint& rhs) {
    return fps(lhs) += rhs;
  }
  friend fps operator+(const mint& lhs, const fps& rhs) {
    return fps(rhs) += lhs;
  }
  friend fps operator+(const fps& lhs, const fps& rhs) {
    return fps(lhs) += rhs;
  }
  friend fps operator-(const fps& lhs, const mint& rhs) {
    return fps(lhs) -= rhs;
  }
  friend fps operator-(const mint& lhs, const fps& rhs) {
    return fps({lhs}) -= rhs;
  }
  friend fps operator-(const fps& lhs, const fps& rhs) {
    return fps(lhs) -= rhs;
  }
  friend fps operator*(const fps& lhs, const mint& rhs) {
    return fps(lhs) *= rhs;
  }
  friend fps operator*(const mint& lhs, const fps& rhs) {
    return fps(rhs) *= lhs;
  }
  friend fps operator*(const fps& lhs, const fps& rhs) {
    return fps(lhs) *= rhs;
  }
  friend fps operator/(const fps& lhs, const mint& rhs) {
    return fps(lhs) /= rhs;
  }

  friend fps operator>>(const fps& f, int w) { return fps(f) >>= w; }
  friend fps operator<<(const fps& f, int w) { return fps(f) <<= w; }

  friend fps diff(fps f) {
    mint coeff = 1;
    for (int i = 1; i < f.size(); i++) {
      f[i] *= coeff;
      coeff++;
    }
    return f >>= 1;
  }

  friend fps integral(fps f) {
    static int mod = mint::mod();
    std::vector<mint> minv(f.size() + 1);
    minv[1] = 1;
    for (int i = 2; i <= f.size(); i++) {
      minv[i] = -minv[mod % i] * (mod / i);
    }
    for (int i = 0; i < f.size(); i++) {
      f[i] *= minv[i + 1];
    }
    return f <<= 1;
  }

  friend std::istream& operator>>(std::istream& is, fps& rhs) {
    for (mint& x : rhs.a) is >> x;
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
  std::vector<mint> a;
};

}  // namespace cp