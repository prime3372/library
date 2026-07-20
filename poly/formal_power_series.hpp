#pragma once

#include <algorithm>
#include <cassert>
#include <concepts>
#include <iostream>
#include <vector>

#include "poly/convolution.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T>
  requires (is_static_modint_v<T> && is_prime(T::mod()) || std::same_as<T, long long>)
struct formal_power_series {
private:
  using fps = formal_power_series;

public:
  formal_power_series() {}
  explicit formal_power_series(int n) : f(n) {}
  explicit formal_power_series(int n, T val) : f(n, val) {}
  explicit formal_power_series(const std::vector<T>& v) : f(v) {}

  T& operator[](int i) {
    assert(0 <= i);
    if (i >= size()) resize(i + 1);
    return f[i];
  }
  const T& operator[](int i) const {
    assert(0 <= i && i < size());
    return f[i];
  };

  T& front() { return f.front(); }
  const T& front() const { return f.front(); }

  T& back() { return f.back(); }
  const T& back() const { return f.back(); }

  fps& operator+=(const T& rhs) { return *this += fps(1, rhs); }
  fps& operator+=(const fps& rhs) {
    if (rhs.size() > size()) f.resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] += rhs[i];
    return *this;
  }

  fps& operator-=(const T& rhs) { return *this -= fps(1, rhs); }
  fps& operator-=(const fps& rhs) {
    if (rhs.size() > size()) f.resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] -= rhs[i];
    return *this;
  }

  fps& operator*=(const T& rhs) {
    for (int i = 0; i < size(); i++) f[i] *= rhs;
    return *this;
  }
  fps& operator*=(const fps& rhs) {
    f = convolution(f, rhs.f);
    return *this;
  }

  fps& operator/=(const T& rhs) {
    for (int i = 0; i < size(); i++) f[i] /= rhs;
    return *this;
  }

  fps operator+() const { return *this; }
  fps operator-() const { return fps() - *this; }

  T operator()(const T& x) const {
    T r = 0, w = 1;
    for (const T& v : f) {
      r += w * v;
      w *= x;
    }
    return r;
  }

  fps inv(int n) const {
    assert(!empty() && front() != 0);
    fps res(1, front().inv());
    for (int step = 0; 1 << step < n; step++) {
      res = res * (2 - res * prefix(1 << (step + 1)));
      res.resize(1 << (step + 1));
    }
    return res.prefix(n);
  }

  fps diff() const {
    if (empty()) return fps();
    fps res(size() - 1);
    T coeff = 1;
    for (int i = 1; i < size(); i++) {
      res[i - 1] = (*this)[i] * coeff;
      coeff++;
    }
    return res;
  }

  fps integral() const {
    if (empty()) return fps(1);
    fps res(size() + 1);
    T coeff = 1;
    res[1] = 1;
    int mod = T::mod();
    for (int i = 2; i <= size(); i++) {
      res[i] = -res[mod % i] * (mod / i);
    }
    for (int i = 0; i < size(); i++) {
      res[i + 1] *= (*this)[i];
    }
    return res;
  }

  friend fps operator+(const fps& lhs, const T& rhs) { return fps(lhs) += rhs; }
  friend fps operator+(const T& lhs, const fps& rhs) { return fps(1, lhs) += rhs; }
  friend fps operator+(const fps& lhs, const fps& rhs) { return fps(lhs) += rhs; }
  friend fps operator-(const fps& lhs, const T& rhs) { return fps(lhs) -= rhs; }
  friend fps operator-(const T& lhs, const fps& rhs) { return fps(1, lhs) -= rhs; }
  friend fps operator-(const fps& lhs, const fps& rhs) { return fps(lhs) -= rhs; }
  friend fps operator*(const fps& lhs, const T& rhs) { return fps(lhs) *= rhs; }
  friend fps operator*(const T& lhs, const fps& rhs) { return fps(rhs) *= lhs; }
  friend fps operator*(const fps& lhs, const fps& rhs) { return fps(lhs) *= rhs; }
  friend fps operator/(const fps& lhs, const T& rhs) { return fps(lhs) /= rhs; }
  friend fps operator/(const T& lhs, const fps& rhs) { return fps(rhs) /= lhs; }

  int size() const { return int(f.size()); }
  bool empty() const { return f.empty(); }
  void resize(int n) { f.resize(n); }
  void shrink() { while (!empty() && back() == 0) f.pop_back(); }

  fps prefix(int n) const {
    fps g(n);
    for (int i = 0; i < std::min(n, size()); i++) g[i] = f[i];
    return g;
  }

  void swap(fps& other) { f.swap(other.f); }
  void clear() { f.clear(); }

  friend std::istream& operator>>(std::istream& is, fps& rhs) {
    for (int i = 0; i < rhs.size(); i++) is >> rhs[i];    
    return is;
  }

  friend std::ostream& operator<<(std::ostream& os, const fps& rhs) {
    for (int i = 0; i < rhs.size(); i++) {
      os << rhs[i];
      if (i != rhs.size() - 1) os << " ";
    }
    return os;
  }

private: 
  std::vector<T> f;
};

} // namespace cp;