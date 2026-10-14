#pragma once

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <vector>

#include "number/is-prime.hpp"
#include "poly/convolution.hpp"
#include "util/type-traits.hpp"

namespace cp {

template <class mint>
  requires(internal::is_static_modint_v<mint> && is_prime(mint::mod()))
struct FormalPowerSeries : public std::vector<mint> {
 public:
  using Self = FormalPowerSeries;
  using Base = std::vector<mint>;
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

  Self& operator+=(const mint& rhs) {
    if (empty()) resize(1);
    (*this)[0] += rhs;
    return *this;
  }
  Self& operator+=(const Self& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < int(rhs.size()); i++) (*this)[i] += rhs[i];
    return *this;
  }
  Self& operator-=(const mint& rhs) {
    if (empty()) resize(1);
    (*this)[0] += rhs;
    return *this;
  }
  Self& operator-=(const Self& rhs) {
    if (rhs.size() > size()) resize(rhs.size());
    for (int i = 0; i < int(rhs.size()); i++) (*this)[i] -= rhs[i];
    return *this;
  }
  Self& operator*=(const mint& rhs) {
    for (int i = 0; i < int(size()); i++) (*this)[i] *= rhs;
    return *this;
  }
  Self& operator*=(const Self& rhs) {
    return *this = Self(convolution(*this, rhs));
  }
  Self& operator/=(const mint& rhs) {
    for (int i = 0; i < int(size()); i++) (*this)[i] /= rhs;
    return *this;
  }

  Self& operator>>=(int w) {
    erase(begin(), begin() + std::min(w, int(size())));
    return *this;
  }
  Self& operator<<=(int w) {
    insert(begin(), w, 0);
    return *this;
  }

  Self operator+() const { return *this; }
  Self operator-() const { return Self() - *this; }

  Self prefix(int n) const {
    Self b(begin(), begin() + std::min(n, int(size())));
    b.resize(n);
    return b;
  }

  friend Self operator+(const Self& lhs, const mint& rhs) {
    return Self(lhs) += rhs;
  }
  friend Self operator+(const mint& lhs, const Self& rhs) {
    return Self(rhs) += lhs;
  }
  friend Self operator+(const Self& lhs, const Self& rhs) {
    return Self(lhs) += rhs;
  }
  friend Self operator-(const Self& lhs, const mint& rhs) {
    return Self(lhs) -= rhs;
  }
  friend Self operator-(const mint& lhs, const Self& rhs) {
    return Self{lhs} -= rhs;
  }
  friend Self operator-(const Self& lhs, const Self& rhs) {
    return Self(lhs) -= rhs;
  }
  friend Self operator*(const Self& lhs, const mint& rhs) {
    return Self(lhs) *= rhs;
  }
  friend Self operator*(const mint& lhs, const Self& rhs) {
    return Self(rhs) *= lhs;
  }
  friend Self operator*(const Self& lhs, const Self& rhs) {
    return Self(lhs) *= rhs;
  }
  friend Self operator/(const Self& lhs, const mint& rhs) {
    return Self(lhs) /= rhs;
  }

  friend Self operator>>(const Self& f, int w) { return Self(f) >>= w; }
  friend Self operator<<(const Self& f, int w) { return Self(f) <<= w; }
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