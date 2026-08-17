#pragma once

#include <cassert>
#include <iostream>
#include <vector>

#include "util/type_traits.hpp"
#include "util/io_utility.hpp"

namespace cp {

template <class T> struct matrix {
 public:
  matrix() : h(0), w(0) {}
  explicit matrix(int _h, int _w) : h(_h), w(_w), d(_h, std::vector<T>(_w)) {}

  int height() const { return h; }
  int width() const { return w; }

  std::vector<T>& operator[](int i) {
    assert(0 <= i && i < h);
    return d[i];
  }
  const std::vector<T>& operator[](int i) const {
    assert(0 <= i && i < h);
    return d[i];
  }

  matrix& operator+=(const matrix& rhs) {
    assert(h == rhs.h && w == rhs.w);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        (*this)[i][j] += rhs[i][j];
      }
    }
    return *this;
  }

  matrix& operator*=(const T& rhs) {
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        (*this)[i][j] *= rhs;
      }
    }
    return *this;
  }
  
  matrix operator*=(const matrix& rhs) {
    assert(w == rhs.h);
    matrix res(h, rhs.w);
    for (int i = 0; i < h; i++) {
      for (int k = 0; k < w; k++) {
        for (int j = 0; j < rhs.w; j++) {
          res[i][j] += (*this)[i][k] * rhs[k][j];
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
    for (int i = 0; i < n; i++) res[i][i] = 1;    
    return res;
  }

  matrix pow(long long n) const {
    assert(h == w);
    assert(0 <= n);
    matrix r = unit(h), mat = *this;
    while (n) {
      if (n & 1) r *= mat;
      mat *= mat;
      n >>= 1;
    }
    return r;
  }

  friend std::ostream& operator<<(std::ostream& os, const matrix& mat) {
    for (int i = 0; i < mat.h; i++) {
      for (int j = 0; j < mat.w; j++) {
        os << mat[i][j];
        if (j != mat.w - 1) os << " ";
      }
      if (i != mat.h - 1) os << "\n";
    }
    return os;
  }

 private:
  int h, w;
  std::vector<std::vector<T>> d;
};

} // namespace cp