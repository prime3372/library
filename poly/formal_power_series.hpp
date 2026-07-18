#pragma once

#include <cassert>
#include <concepts>
#include <vector>

#include "poly/convolution.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class> struct formal_power_series {};

template <class mint> requires is_static_modint_v<mint> && (is_prime(mint::mod()))
struct formal_power_series<mint> {
private:
  using fps = formal_power_series;

public:
  static constexpr int mod() { return mint::mod(); }

  formal_power_series() {}
  formal_power_series(int n) : f(n) {}
  formal_power_series(const std::vector<mint>& v) : f(v) {}

  mint& operator[](int i) {
    assert(0 <= i);
    if (i >= size()) resize(i + 1);
    return f[i];
  }
  const mint& operator[](int i) const {
    assert(0 <= i && i < size());
    return f[i];
  };

  fps& operator+=(const fps& rhs) {
    if (rhs.size() > size()) f.resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] += rhs[i];
    return *this;
  }
  fps& operator-=(const fps& rhs) {
    if (rhs.size() > size()) f.resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] -= rhs[i];
    return *this;
  }
  fps& operator*=(const fps& rhs) {
    f = convolution(f, rhs.f);
    return *this;
  }
  fps& operator*=(const mint& rhs) {
    for (int i = 0; i < size(); i++) f[i] *= rhs;
    return *this;
  }
  fps& operator/=(const mint& rhs) {
    for (int i = 0; i < size(); i++) f[i] /= rhs;
    return *this;
  }

  friend fps operator+(const fps& lhs, const fps& rhs) { return fps(lhs) += rhs; }
  friend fps operator-(const fps& lhs, const fps& rhs) { return fps(lhs) -= rhs; }
  friend fps operator*(const fps& lhs, const fps& rhs) { return fps(lhs) *= rhs; }
  friend fps operator*(const fps& lhs, const mint& rhs) { return fps(lhs) *= rhs; }
  friend fps operator*(const mint& lhs, const fps& rhs) { return fps(rhs) *= lhs; }
  friend fps operator/(const fps& lhs, const mint& rhs) { return fps(lhs) /= rhs; }
  friend fps operator/(const mint& lhs, const fps& rhs) { return fps(rhs) /= lhs; }

  int size() const { return int(f.size()); }
  void resize(int n) { f.resize(n); }
  void swap(fps& other) { f.swap(other.f); }

private: 
  std::vector<mint> f;
};

template <> struct formal_power_series<long long> {
  using fps = formal_power_series;

public:
  formal_power_series() {}
  formal_power_series(int n) : f(n) {}
  formal_power_series(const std::vector<long long>& v) : f(v) {}

  long long& operator[](int i) {
    assert(0 <= i);
    if (i >= size()) resize(i + 1);
    return f[i];
  }
  const long long& operator[](int i) const {
    assert(0 <= i && i < size());
    return f[i];
  };

  fps& operator+=(const fps& rhs) {
    if (size() < rhs.size()) f.resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] += rhs[i];
    return *this;
  }
  fps& operator-=(const fps& rhs) {
    if (size() < rhs.size()) f.resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] -= rhs[i];
    return *this;
  }
  fps& operator*=(const fps& rhs) {
    f = convolution(f, rhs.f);
    return *this;
  }
  fps& operator*=(long long rhs) {
    for (int i = 0; i < size(); i++) f[i] *= rhs;
    return *this;
  }
  fps& operator/=(long long rhs) {
    for (int i = 0; i < size(); i++) f[i] /= rhs;
    return *this;
  }

  friend fps operator+(const fps& lhs, const fps& rhs) { return fps(lhs) += rhs; }
  friend fps operator-(const fps& lhs, const fps& rhs) { return fps(lhs) -= rhs; }
  friend fps operator*(const fps& lhs, const fps& rhs) { return fps(lhs) *= rhs; }
  friend fps operator*(const fps& lhs, long long rhs) { return fps(lhs) *= rhs; }
  friend fps operator*(long long lhs, const fps& rhs) { return fps(rhs) *= lhs; }
  friend fps operator/(const fps& lhs, long long rhs) { return fps(lhs) /= rhs; }
  friend fps operator/(long long lhs, const fps& rhs) { return fps(rhs) /= lhs; }

  int size() const { return int(f.size()); }
  void resize(int n) { f.resize(n); }
  void swap(fps& other) { f.swap(other.f); }

private: 
  std::vector<long long> f;
};

} // namespace cp