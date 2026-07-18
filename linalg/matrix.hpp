#pragma once

#include <cassert>
#include <iostream>
#include <type_traits>
#include <vector>

#include "algebra/add_mul.hpp"
#include "algebra/semiring.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T>
   requires (semiring<T> || std::is_arithmetic_v<T> || is_modint_v<T>)
struct matrix {
private:
  using R = std::conditional_t<semiring<T>, T, add_mul<T>>;
  using S = typename R::S;

public:
  struct row {
  public:
    row() : row(0) {}    
    explicit row(int _w) : w(_w), d(_w, R::zero()) {}
    explicit row(int _w, S x) : w(_w), d(_w, x) {}

    S& operator[](int j) {
      assert(0 <= j && j < w);
      return d[j];
    }
    const S& operator[](int j) const {
      assert(0 <= j && j < w);
      return d[j];
    }
    void swap(row& r) {
      assert(w == r.w);
      d.swap(r.d);
    }
    row& operator=(const row& r) {
      assert(w == r.w);
      d = r.d;
      return *this;
    }

  private:
    int w;
    std::vector<S> d;
  };

  matrix() : h(0), w(0) {}
  explicit matrix(int _h, int _w) : h(_h), w(_w), d(_h, row(_w)) {}

  int height() const { return h; }
  int width() const { return w; }

  row& operator[](int i) {
    assert(0 <= i && i < h);
    return d[i];
  }
  const row& operator[](int i) const {
    assert(0 <= i && i < h);
    return d[i];
  }

  matrix& operator+=(const matrix& rhs) {
    assert(h == rhs.h && w == rhs.w);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        (*this)[i][j] = R::add((*this)[i][j], rhs[i][j]);
      }
    }
    return *this;
  }

  matrix& operator*=(const S& rhs) {
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        (*this)[i][j] = R::mul((*this)[i][j], rhs);
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
          res[i][j] = R::add(res[i][j], R::mul((*this)[i][k], rhs[k][j]));
        }
      }
    }
    return *this = res;
  }

  friend matrix operator+(const matrix& lhs, const matrix& rhs) { return matrix(lhs) += rhs; }  
  friend matrix operator*(const matrix& lhs, const S& rhs) { return matrix(lhs) *= rhs; }
  friend matrix operator*(const S& lhs, const matrix& rhs) { return matrix(rhs) *= lhs; }
  friend matrix operator*(const matrix& lhs, const matrix& rhs) { return matrix(lhs) *= rhs; }

  static matrix unit(int n) {
    matrix res(n, n);
    for (int i = 0; i < n; i++) res[i][i] = R::one();    
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

  friend std::istream& operator>>(std::istream& is, matrix& mat) {
    for (int i = 0; i < mat.h; i++) {
      for (int j = 0; j < mat.w; j++) {
        is >> mat[i][j];
      }
    }
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, matrix& mat) {
    for (int i = 0; i < mat.h; i++) {
      for (int j = 0; j < mat.w; j++) {
        os << mat[i][j] << " ";
      }
      if (i != mat.h - 1) os << "\n";
    }
    return os;
  }

private:
  int h, w;
  std::vector<row> d;
};

} // namespace cp