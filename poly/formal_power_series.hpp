#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "poly/convolution.hpp"
#include "util/io_utility.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class>
struct formal_power_series {};

template <class mint>
  requires internal::is_static_modint_v<mint> && (is_prime(mint::mod()))
struct formal_power_series<mint> {
private:
  using fps = formal_power_series;

public:
  formal_power_series() {}
  explicit formal_power_series(int n) : a(n) {}
  explicit formal_power_series(int n, const mint& val) : a(n, val) {}
  explicit formal_power_series(const std::vector<mint>& _a) : a(_a) {}

  mint& operator[](int i) {
    assert(0 <= i && i < size());
    return a[i];
  }
  const mint& operator[](int i) const {
    assert(0 <= i && i < size());
    return a[i];
  }

  fps& operator+=(const mint& rhs) {
    return *this += fps(1, rhs);
  }
  fps& operator+=(const fps& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) a[i] += rhs[i];
    return *this;
  }

  fps& operator-=(const mint& rhs) {
    return *this -= fps(1, rhs);
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

  fps operator+() const { return *this; }
  fps operator-() const { return fps() - *this; }

  friend fps operator+(const fps& lhs, const mint& rhs) { return fps(lhs) += rhs; }
  friend fps operator+(const mint& lhs, const fps& rhs) { return fps(rhs) += lhs; }
  friend fps operator+(const fps& lhs, const fps& rhs) { return fps(lhs) += rhs; }
  friend fps operator-(const fps& lhs, const mint& rhs) { return fps(lhs) -= rhs; }
  friend fps operator-(const mint& lhs, const fps& rhs) { return fps(1, lhs) -= rhs; }
  friend fps operator-(const fps& lhs, const fps& rhs) { return fps(lhs) -= rhs; }
  friend fps operator*(const fps& lhs, const mint& rhs) { return fps(lhs) *= rhs; }
  friend fps operator*(const mint& lhs, const fps& rhs) { return fps(rhs) *= lhs; }
  friend fps operator*(const fps& lhs, const fps& rhs) { return fps(lhs) *= rhs; }
  friend fps operator/(const fps& lhs, const mint& rhs) { return fps(lhs) /= rhs; }
  friend fps operator/(const mint& lhs, const fps& rhs) { return fps(rhs) /= lhs; }

  fps operator>>(int w) const {
    if (size() <= w) return fps();
    auto b = a;
    b.erase(b.begin(), b.begin() + w);
    return fps(b);
  }

  fps operator<<(int w) const {
    auto b = a;
    b.insert(b.begin(), w, 0);
    return fps(b);
  }

  int size() const { return int(a.size()); }
  bool empty() const { return a.empty(); }
  void resize(int n) { a.resize(n); }

  void swap(fps& other) { a.swap(other.a); }
  void clear() { a.clear(); }

  fps prefix(int n) const {
    fps f(n);
    for (int i = 0; i < std::min(n, size()); i++) f[i] = a[i];
    return f;
  }

  fps diff() const {
    if (a.empty()) return fps();
    fps ans(size() - 1);
    mint coeff = 1;
    for (int i = 1; i < size(); i++) {
      ans[i - 1] = a[i] * coeff;
      coeff++;
    }
    return ans;
  }

  fps integral() const {
    if (a.empty()) return fps(1);
    fps res(size() + 1);
    res[1] = 1;
    int mod = mint::mod();
    for (int i = 2; i <= size(); i++) {
      res[i] = -res[mod % i] * (mod / i);
    }
    for (int i = 0; i < size(); i++) {
      res[i + 1] *= a[i];
    }
    return res;
  }

  fps inv() const { return inv(size()); }
  fps inv(int n) const {
    assert(0 <= n);
    assert(!a.empty() && a[0] != 0);
    fps g(1, a[0].inv());
    for (int i = 0; (1 << i) < n; i++) {
      g = 2 * g - g * g * prefix(1 << (i + 1));
      g.resize(1 << (i + 1));
    }
    return g.prefix(n);
  }

  fps log() const { return log(size()); }
  fps log(int n) const {
    assert(0 <= n);
    assert(!a.empty() && a[0] == 1);
    fps g = prefix(n);
    return (g.diff() * g.inv()).integral().prefix(n);
  }

  fps exp() const { return exp(size()); }
  fps exp(int n) const {
    assert(0 <= n);
    assert(a.empty() || a[0] == 0);
    fps g(1, 1);
    for (int i = 0; (1 << i) < n; i++) {
      g = g - g * g.log(1 << (i + 1)) + g * prefix(1 << (i + 1));
      g.resize(1 << (i + 1));
    }
    return g.prefix(n);
  }

  fps pow(long long k) { return pow(k, size()); }
  fps pow(long long k, int n) const {
    assert(0 <= k && 0 <= n);
    if (k == 0) {
      fps ans(n);
      if (n) ans[0] = 1;
      return ans;
    }
    int up = int((n - 1) / k + 1);
    for (int i = 0; i < up; i++) {
      if (a[i] != 0) {
        mint minv = a[i].inv();
        fps ans = (((*this * minv) >> i).log(n) * k).exp(n);
        ans *= a[i].pow(k);
        ans = (ans << int(i * k)).prefix(n);
        return ans.prefix(n);
      }
    }
    return fps(n);
  }

  mint eval(const mint& x) const {
    mint r = 0, w = 1;
    for (const mint& v : a) {
      r += w * v;
      w *= x;
    }
    return r;
  }

  // for debugging
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

template <>
struct formal_power_series<long long> {
private:
  using fps = formal_power_series;

public:
  formal_power_series() {}
  explicit formal_power_series(int n) : a(n) {}
  explicit formal_power_series(int n, long long val) : a(n, val) {}
  explicit formal_power_series(const std::vector<long long>& _a) : a(_a) {}

  long long& operator[](int i) {
    assert(0 <= i && i < size());
    return a[i];
  }
  const long long& operator[](int i) const {
    assert(0 <= i && i < size());
    return a[i];
  }

  fps& operator+=(long long rhs) {
    return *this += fps(1, rhs);
  }
  fps& operator+=(const fps& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) a[i] += rhs[i];
    return *this;
  }

  fps& operator-=(long long rhs) {
    return *this -= fps(1, rhs);
  }
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
    a = convolution(a, rhs.a);
    return *this;
  }

  fps& operator/=(long long rhs) {
    for (int i = 0; i < size(); i++) a[i] /= rhs;
    return *this;
  }

  fps operator+() const { return *this; }
  fps operator-() const { return fps() - *this; }

  friend fps operator+(const fps& lhs, long long rhs) { return fps(lhs) += rhs; }
  friend fps operator+(long long lhs, const fps& rhs) { return fps(rhs) += lhs; }
  friend fps operator+(const fps& lhs, const fps& rhs) { return fps(lhs) += rhs; }
  friend fps operator-(const fps& lhs, long long rhs) { return fps(lhs) -= rhs; }
  friend fps operator-(long long lhs, const fps& rhs) { return fps(1, lhs) -= rhs; }
  friend fps operator-(const fps& lhs, const fps& rhs) { return fps(lhs) -= rhs; }
  friend fps operator*(const fps& lhs, long long rhs) { return fps(lhs) *= rhs; }
  friend fps operator*(long long lhs, const fps& rhs) { return fps(rhs) *= lhs; }
  friend fps operator*(const fps& lhs, const fps& rhs) { return fps(lhs) *= rhs; }
  friend fps operator/(const fps& lhs, long long rhs) { return fps(lhs) /= rhs; }
  friend fps operator/(long long lhs, const fps& rhs) { return fps(rhs) /= lhs; }

  fps operator>>(int w) const {
    if (size() <= w) return fps();
    auto b = a;
    b.erase(b.begin(), b.begin() + w);
    return fps(b);
  }

  fps operator<<(int w) const {
    auto b = a;
    b.insert(b.begin(), w, 0);
    return fps(b);
  }

  int size() const { return int(a.size()); }
  bool empty() const { return a.empty(); }
  void resize(int n) { a.resize(n); }

  void swap(fps& other) { a.swap(other.a); }
  void clear() { a.clear(); }

  // for debugging
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

namespace internal {

template <class T>
struct delimiter<formal_power_series<T>> {
  static constexpr char value[] = "\n";
};

} // namespace internal

} // namespace cp