#pragma once

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <vector>

#include "number/is-prime.hpp"
#include "poly/convolution.hpp"
#include "util/type-traits.hpp"

namespace cp {

template <class mint>
requires(internal::is_static_modint_v<mint> && is_prime(mint::mod()))
class FormalPowerSeries : public std::vector<mint> {
  using Base = std::vector<mint>;
  using fps = FormalPowerSeries;

 public:
  using Base::Base;
  using Base::begin;
  using Base::empty;
  using Base::erase;
  using Base::insert;
  using Base::resize;
  using Base::size;

  explicit FormalPowerSeries(const std::vector<mint>& a) : Base(a) {}
  FormalPowerSeries(std::initializer_list<std::pair<int, mint>> il) {
    int n = 0;
    for (const auto& p : il) n = std::max(n, p.first);
    resize(n + 1);
    for (const auto& p : il) (*this)[p.first] = p.second;
  }

  fps& operator+=(const mint& rhs) {
    if (empty()) resize(1);
    (*this)[0] += rhs;
    return *this;
  }
  fps& operator+=(const fps& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < int(rhs.size()); i++) (*this)[i] += rhs[i];
    return *this;
  }
  fps& operator-=(const mint& rhs) {
    if (empty()) resize(1);
    (*this)[0] += rhs;
    return *this;
  }
  fps& operator-=(const fps& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < int(rhs.size()); i++) (*this)[i] -= rhs[i];
    return *this;
  }
  fps& operator*=(const mint& rhs) {
    for (int i = 0; i < int(size()); i++) (*this)[i] *= rhs;
    return *this;
  }
  fps& operator*=(const fps& rhs) {
    return *this = fps(convolution(*this, rhs));
  }
  fps& operator/=(const mint& rhs) {
    for (int i = 0; i < int(size()); i++) (*this)[i] /= rhs;
    return *this;
  }

  fps& operator>>=(int w) {
    erase(begin(), begin() + std::min(w, int(size())));
    return *this;
  }
  fps& operator<<=(int w) {
    insert(begin(), w, 0);
    return *this;
  }

  fps operator+() const { return *this; }
  fps operator-() const { return fps() - *this; }

  fps prefix(int n) const {
    fps b(begin(), begin() + std::min(n, int(size())));
    b.resize(n);
    return b;
  }

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
    return fps{lhs} -= rhs;
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
};

template <class mint> FormalPowerSeries<mint> diff(FormalPowerSeries<mint> f) {
  mint coeff = 1;
  for (int i = 1; i < int(f.size()); i++) {
    f[i] *= coeff;
    coeff++;
  }
  return f >> 1;
}

template <class mint>
FormalPowerSeries<mint> integral(FormalPowerSeries<mint> f) {
  constexpr int m = mint::mod();
  if (f.empty()) return f;
  int n = int(f.size());
  std::vector<mint> minv(n + 1);
  minv[1] = 1;
  for (int i = 2; i <= n; i++) minv[i] = -minv[m % i] * (m / i);
  for (int i = 0; i < n; i++) f[i] *= minv[i + 1];
  return f << 1;
}

}  // namespace cp