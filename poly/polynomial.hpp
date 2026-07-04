#pragma once

#include <cassert>
#include <concepts>
#include <vector>

#include "convolution.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class> struct polynomial {};

template <class mint> requires is_static_modint_v<mint> && (is_prime(mint::mod()))
struct polynomial<mint> {

  static constexpr int mod() { return mint::mod(); }

  polynomial() {}
  polynomial(int n) : f(n) {}
  polynomial(int n, const mint& val) : f(n, val) {}
  polynomial(const std::vector<mint>& v) : f(v) {}

  mint& operator[](int i) {
    assert(0 <= i);
    if (i >= size()) resize(i + 1);
    return f[i];
  }
  const mint& operator[](int i) const {
    assert(0 <= i && i < size());
    return f[i];
  };

  polynomial& operator+=(const polynomial& rhs) {
    static_assert(mod() == rhs.mod(), "modulo must be the same.");
    if (rhs.size() > size()) f.resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] += rhs[i];
    return *this;
  }
  polynomial& operator-=(const polynomial& rhs) {
    static_assert(mod() == rhs.mod(), "modulo must be the same.");
    if (rhs.size() > size()) f.resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] -= rhs[i];
    return *this;
  }
  polynomial& operator*=(const polynomial& rhs) {
    static_assert(mod() == rhs.mod(), "modulo must be the same.");
    f = convolution(f, rhs.f);
    return *this;
  }
  polynomial& operator*=(const mint& rhs) {
    for (int i = 0; i < size(); i++) f[i] *= rhs;
    return *this;
  }
  polynomial& operator/=(const mint& rhs) {
    for (int i = 0; i < size(); i++) f[i] /= rhs;
    return *this;
  }

  friend polynomial operator+(const polynomial& lhs, const polynomial& rhs) { return polynomial(lhs) += rhs; }
  friend polynomial operator-(const polynomial& lhs, const polynomial& rhs) { return polynomial(lhs) -= rhs; }
  friend polynomial operator*(const polynomial& lhs, const polynomial& rhs) { return polynomial(lhs) *= rhs; }
  friend polynomial operator*(const mint& lhs, const polynomial& rhs) { return polynomial(rhs) *= lhs; }
  friend polynomial operator*(const polynomial& lhs, const mint& rhs) { return polynomial(lhs) *= rhs; }
  friend polynomial operator/(const mint& lhs, const polynomial& rhs) { return polynomial(rhs) /= lhs; }
  friend polynomial operator/(const polynomial& lhs, const mint& rhs) { return polynomial(lhs) /= rhs; }

  int size() const { return int(f.size()); }
  void resize(int n) { f.resize(n); }
  void resize(int n, const mint& val) { f.resize(n, val); }
  void swap(polynomial& other) { f.swap(other.f); }

private: 
  std::vector<mint> f;
};

template <> struct polynomial<long long> {
  polynomial() {}
  polynomial(int n) : f(n) {}
  polynomial(int n, long long val) : f(n, val) {}
  polynomial(const std::vector<long long>& v) : f(v) {}

  long long& operator[](int i) {
    assert(0 <= i && i < size());
    return f[i];
  }
  const long long& operator[](int i) const {
    assert(0 <= i && i < size());
    return f[i];
  };

  polynomial& operator+=(const polynomial& rhs) {
    if (size() < rhs.size()) f.resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] += rhs[i];
    return *this;
  }
  polynomial& operator-=(const polynomial& rhs) {
    if (size() < rhs.size()) f.resize(rhs.size());
    for (int i = 0; i < rhs.size(); i++) f[i] -= rhs[i];
    return *this;
  }
  polynomial& operator*=(const polynomial& rhs) {
    f = convolution(f, rhs.f);
    return *this;
  }
  polynomial& operator*=(long long rhs) {
    for (int i = 0; i < size(); i++) f[i] *= rhs;
    return *this;
  }
  polynomial& operator/=(long long rhs) {
    for (int i = 0; i < size(); i++) f[i] /= rhs;
    return *this;
  }

  friend polynomial operator+(const polynomial& lhs, const polynomial& rhs) {
    if (lhs.size() > rhs.size()) return polynomial(lhs) += rhs;
    else return polynomial(rhs) += lhs;
  }
  friend polynomial operator-(const polynomial& lhs, const polynomial& rhs) { return polynomial(lhs) -= rhs; }
  friend polynomial operator*(const polynomial& lhs, const polynomial& rhs) { return polynomial(lhs) *= rhs; }
  friend polynomial operator*(long long lhs, const polynomial& rhs) { return polynomial(rhs) *= lhs; }
  friend polynomial operator*(const polynomial& lhs, long long rhs) { return polynomial(lhs) *= rhs; }
  friend polynomial operator/(long long lhs, const polynomial& rhs) { return polynomial(rhs) /= lhs; }
  friend polynomial operator/(const polynomial& lhs, long long rhs) { return polynomial(lhs) /= rhs; }

  int size() const { return int(f.size()); }
  void resize(int n) { f.resize(n); }
  void resize(int n, long long val) { f.resize(n, val); }
  void swap(polynomial& other) { f.swap(other.f); }

private: 
  std::vector<long long> f;
};

} // namespace cp