#pragma once

#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

#include "util/type_traits.hpp"

namespace cp {

template <class T, auto add = std::plus(), auto mul = std::multiplies(),
          auto zero = []() { return T(0); }, auto one = []() { return T(1); }>
class matrix : public std::vector<std::vector<T>> {
 public:
  using base = std::vector<std::vector<T>>;
  using base::empty;
  using base::size;

  matrix() {}
  explicit matrix(int _h, int _w) : base(_h, std::vector<T>(_w, zero())) {}

  int height() const { return int(size()); }
  int width() const { return empty() ? 0 : int((*this)[0].size()); }

  matrix& operator+=(const matrix& rhs) {
    assert(height() == rhs.height() && width() == rhs.width());
    for (int i = 0; i < height(); i++) {
      for (int j = 0; j < width(); j++) {
        (*this)[i][j] = add((*this)[i][j], rhs[i][j]);
      }
    }
    return *this;
  }

  matrix& operator*=(const T& rhs) {
    for (int i = 0; i < height(); i++) {
      for (int j = 0; j < width(); j++) {
        (*this)[i][j] = mul((*this)[i][j], rhs);
      }
    }
    return *this;
  }

  matrix operator*=(const matrix& rhs) {
    assert(width() == rhs.height());
    matrix res(height(), rhs.width());
    for (int i = 0; i < height(); i++) {
      for (int k = 0; k < width(); k++) {
        for (int j = 0; j < rhs.width(); j++) {
          res[i][j] = add(res[i][j], mul((*this)[i][k], rhs[k][j]));
        }
      }
    }
    return *this = res;
  }

  friend matrix operator+(const matrix& lhs, const matrix& rhs) {
    return matrix(lhs) += rhs;
  }
  friend matrix operator*(const matrix& lhs, const T& rhs) {
    return matrix(lhs) *= rhs;
  }
  friend matrix operator*(const T& lhs, const matrix& rhs) {
    return matrix(rhs) *= lhs;
  }
  friend matrix operator*(const matrix& lhs, const matrix& rhs) {
    return matrix(lhs) *= rhs;
  }

  static matrix unit(int n) {
    matrix res(n, n);
    for (int i = 0; i < n; i++) res[i][i] = one();
    return res;
  }

  matrix pow(long long n) const {
    assert(height() == width());
    assert(0 <= n);
    matrix r = unit(height()), mat = *this;
    while (n) {
      if (n & 1) r *= mat;
      mat *= mat;
      n >>= 1;
    }
    return r;
  }

  friend std::istream& operator>>(std::istream& is, matrix& mat) {
    for (int i = 0; i < mat.height(); i++) {
      for (int j = 0; j < mat.width(); j++) {
        is >> mat[i][j];
      }
    }
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, const matrix& mat) {
    for (int i = 0; i < mat.height(); i++) {
      for (int j = 0; j < mat.width(); j++) {
        os << mat[i][j];
        if (j != mat.width() - 1) os << " ";
      }
      if (i != mat.height() - 1) os << "\n";
    }
    return os;
  }
};

}  // namespace cp