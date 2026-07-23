#pragma once

#include <algorithm>
#include <cassert>
#include <concepts>
#include <iostream>
#include <vector>

#include "poly/convolution.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class>
struct formal_power_series {};

template <class mint>
  requires (is_static_modint_v<mint> && is_prime(mint::mod()))
struct formal_power_series<mint> {
private:
  using fps = formal_power_series;

public:
  formal_power_series() {}
  explicit formal_power_series(int n) : f(n) {}
  explicit formal_power_series(int n, const mint& val) : f(n, val) {}
  explicit formal_power_series(const std::vector<mint>& v) : f(v) {}

  mint& operator[](int i) {
    assert(0 <= i);
    if (size() <= i) resize(i + 1);
    return f[i];
  }

  mint get(int i) const {
    assert(0 <= i);
    return i < size() ? f[i] : 0;
  }

  fps& operator+=(const mint& rhs) {
    return *this += fps(1, rhs);
  }
  fps& operator+=(const fps& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] += rhs.get(i);
    return *this;
  }

  fps& operator-=(const mint& rhs) {
    return *this -= fps(1, rhs);
  }
  fps& operator-=(const fps& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] -= rhs.get(i);
    return *this;
  }

  fps& operator*=(const mint& rhs) {
    for (int i = 0; i < size(); i++) f[i] *= rhs;
    return *this;
  }
  fps& operator*=(const fps& rhs) {
    f = convolution(f, rhs.f);
    return *this;
  }

  fps& operator/=(const mint& rhs) {
    for (int i = 0; i < size(); i++) f[i] /= rhs;
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
    auto g = f;
    g.erase(g.begin(), g.begin() + w);
    return fps(g);
  }

  fps operator<<(int w) const {
    auto g = f;
    g.insert(g.begin(), w, 0);
    return fps(g);
  }

  int size() const { return int(f.size()); }
  bool empty() const { return f.empty(); }
  void resize(int n) { f.resize(n); }

  void swap(fps& other) { f.swap(other.f); }
  void clear() { f.clear(); }

  fps prefix(int n) const {
    fps g(n);
    for (int i = 0; i < std::min(n, size()); i++) g[i] = f[i];
    return g;
  }

  fps diff() const {
    if (f.empty()) return fps();
    fps res(size() - 1);
    mint coeff = 1;
    for (int i = 1; i < size(); i++) {
      res[i - 1] = f[i] * coeff;
      coeff++;
    }
    return res;
  }

  fps integral() const {
    if (f.empty()) return fps(1);
    fps res(size() + 1);
    res[1] = 1;
    int mod = mint::mod();
    for (int i = 2; i <= size(); i++) {
      res[i] = -res[mod % i] * (mod / i);
    }
    for (int i = 0; i < size(); i++) {
      res[i + 1] *= f[i];
    }
    return res;
  }

  fps inv() const {
    return inv(size());
  }
  fps inv(int n) const {
    assert(0 <= n);
    assert(!f.empty() && f[0] != 0);
    fps g(1, f[0].inv());
    for (int i = 0; (1 << i) < n; i++) {
      g = 2 * g - g * g * prefix(1 << (i + 1));
      g.resize(1 << (i + 1));
    }
    return g.prefix(n);
  }

  fps log() const {
    return log(size());
  }
  fps log(int n) const {
    assert(0 <= n);
    assert(!f.empty() && f[0] == 1);
    fps g = prefix(n);
    return (g.diff() * g.inv()).integral().prefix(n);
  }

  fps exp() const {
    return exp(size());
  }
  fps exp(int n) const {
    assert(0 <= n);
    assert(f.empty() || f[0] == 0);
    fps g(1, 1);
    for (int i = 0; (1 << i) < n; i++) {
      g = g - g * g.log(1 << (i + 1)) + g * prefix(1 << (i + 1));
      g.f.resize(1 << (i + 1));
    }
    return g.prefix(n);
  }

  fps pow(long long k) {
    return pow(k, size());
  }
  fps pow(long long k, int n) const {
    assert(0 <= k && 0 <= n);
    if (k == 0) {
      fps res(n);
      if (n) res[0] = 1;
      return res;
    }
    int up = int((n - 1) / k + 1);
    for (int i = 0; i < up; i++) {
      if (f[i] != 0) {
        mint minv = f[i].inv();
        fps res = (((*this * minv) >> i).log(n) * k).exp(n);
        res *= f[i].pow(k);
        res = (res << int(i * k)).prefix(n);
        return res.prefix(n);
      }
    }
    return fps(n);
  }

  mint eval(const mint& x) const {
    mint r = 0, w = 1;
    for (const mint& v : f) {
      r += w * v;
      w *= x;
    }
    return r;
  }

  friend std::istream& operator>>(std::istream& is, fps& r) {
    for (mint& x : r.f) is >> x;
    return is;
  }

  friend std::ostream& operator<<(std::ostream& os, const fps& r) {
    for (int i = 0; i < r.size(); i++) {
      os << r.f[i];
      if (i != r.size() - 1) os << " ";
    }
    return os;
  }

private:
  std::vector<mint> f;
};

template <>
struct formal_power_series<long long> {
private:
  using fps = formal_power_series;

public:
  formal_power_series() {}
  explicit formal_power_series(int n) : f(n) {}
  explicit formal_power_series(int n, long long val) : f(n, val) {}
  explicit formal_power_series(const std::vector<long long>& v) : f(v) {}

  long long& operator[](int i) {
    assert(0 <= i);
    if (size() <= i) resize(i + 1);
    return f[i];
  }

  long long get(int i) const {
    assert(0 <= i);
    return i < size() ? f[i] : 0;
  }

  fps& operator+=(long long rhs) {
    return *this += fps(1, rhs);
  }
  fps& operator+=(const fps& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] += rhs.get(i);
    return *this;
  }

  fps& operator-=(long long rhs) {
    return *this -= fps(1, rhs);
  }
  fps& operator-=(const fps& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] -= rhs.get(i);
    return *this;
  }

  fps& operator*=(long long rhs) {
    for (int i = 0; i < size(); i++) f[i] *= rhs;
    return *this;
  }
  fps& operator*=(const fps& rhs) {
    f = convolution(f, rhs.f);
    return *this;
  }

  fps& operator/=(long long rhs) {
    for (int i = 0; i < size(); i++) f[i] /= rhs;
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
    auto g = f;
    g.erase(g.begin(), g.begin() + w);
    return fps(g);
  }

  fps operator<<(int w) const {
    auto g = f;
    g.insert(g.begin(), w, 0);
    return fps(g);
  }

  int size() const { return int(f.size()); }
  bool empty() const { return f.empty(); }
  void resize(int n) { f.resize(n); }

  void swap(fps& other) { f.swap(other.f); }
  void clear() { f.clear(); }

  long long eval(long long x) const {
    long long r = 0, w = 1;
    for (long long v : f) {
      r += w * v;
      w *= x;
    }
    return r;
  }

  friend std::istream& operator>>(std::istream& is, fps& r) {
    for (long long& x : r.f) is >> x;
    return is;
  }

  friend std::ostream& operator<<(std::ostream& os, const fps& r) {
    for (int i = 0; i < r.size(); i++) {
      os << r.f[i];
      if (i != r.size() - 1) os << " ";
    }
    return os;
  }

private:
  std::vector<long long> f;
};

} // namespace cp