#pragma once

#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

#include "util/type-traits.hpp"

namespace cp {

template <class T, auto add = std::plus<T>(), auto mul = std::multiplies<T>(),
          auto zero = []() { return T(0); }, auto one = []() { return T(1); }>
class Matrix : public std::vector<std::vector<T>> {
 public:
  using Base = std::vector<std::vector<T>>;
  using Base::empty;
  using Base::size;

  Matrix() {}
  explicit Matrix(int _h, int _w) : Base(_h, std::vector<T>(_w, zero())) {}

  int height() const { return int(size()); }
  int width() const { return empty() ? 0 : int((*this)[0].size()); }

  Matrix& operator+=(const Matrix& rhs) {
    assert(height() == rhs.height() && width() == rhs.width());
    for (int i = 0; i < height(); i++) {
      for (int j = 0; j < width(); j++) {
        (*this)[i][j] = add((*this)[i][j], rhs[i][j]);
      }
    }
    return *this;
  }

  Matrix& operator*=(const T& rhs) {
    for (int i = 0; i < height(); i++) {
      for (int j = 0; j < width(); j++) {
        (*this)[i][j] = mul((*this)[i][j], rhs);
      }
    }
    return *this;
  }

  Matrix operator*=(const Matrix& rhs) {
    assert(width() == rhs.height());
    Matrix res(height(), rhs.width());
    for (int i = 0; i < height(); i++) {
      for (int k = 0; k < width(); k++) {
        for (int j = 0; j < rhs.width(); j++) {
          res[i][j] = add(res[i][j], mul((*this)[i][k], rhs[k][j]));
        }
      }
    }
    return *this = res;
  }

  friend Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    return Matrix(lhs) += rhs;
  }
  friend Matrix operator*(const Matrix& lhs, const T& rhs) {
    return Matrix(lhs) *= rhs;
  }
  friend Matrix operator*(const T& lhs, const Matrix& rhs) {
    return Matrix(rhs) *= lhs;
  }
  friend Matrix operator*(const Matrix& lhs, const Matrix& rhs) {
    return Matrix(lhs) *= rhs;
  }

  static Matrix unit(int n) {
    Matrix res(n, n);
    for (int i = 0; i < n; i++) res[i][i] = one();
    return res;
  }

  Matrix pow(long long n) const {
    assert(height() == width());
    assert(0 <= n);
    Matrix r = unit(height()), mat = *this;
    while (n) {
      if (n & 1) r *= mat;
      mat *= mat;
      n >>= 1;
    }
    return r;
  }
};

}  // namespace cp