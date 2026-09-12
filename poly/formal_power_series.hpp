#pragma once

#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <vector>

#include "poly/convolution.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class mint> requires(internal::is_static_modint_v<mint>)
class formal_power_series : public std::vector<mint> {
  using base = std::vector<mint>;
  using fps = formal_power_series;

 public:
  using base::base;
  using base::begin;
  using base::empty;
  using base::erase;
  using base::insert;
  using base::resize;
  using base::size;

  explicit formal_power_series(const std::vector<mint>& a) : base(a) {}
  formal_power_series(std::initializer_list<std::pair<int, mint>> il) {
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

  friend std::istream& operator>>(std::istream& is, fps& rhs) {
    for (mint& x : rhs) is >> x;
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, const fps& rhs) {
    for (int i = 0; i < int(rhs.size()); i++) {
      os << rhs[i];
      if (i != int(rhs.size()) - 1) os << " ";
    }
    return os;
  }
};

template <class mint>
formal_power_series<mint> diff(formal_power_series<mint> f) {
  mint coeff = 1;
  for (int i = 1; i < int(f.size()); i++) {
    f[i] *= coeff;
    coeff++;
  }
  return f >>= 1;
}

template <class mint>
formal_power_series<mint> integral(formal_power_series<mint> f) {
  if (f.empty()) return f;
  int m = mint::mod();
  std::vector<mint> minv(f.size() + 1);
  minv[1] = 1;
  for (int i = 2; i <= int(f.size()); i++) {
    minv[i] = -minv[m % i] * (m / i);
  }
  for (int i = 0; i < int(f.size()); i++) {
    f[i] *= minv[i + 1];
  }
  return f <<= 1;
}

}  // namespace cp