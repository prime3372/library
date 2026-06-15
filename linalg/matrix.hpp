#pragma once

#include <cassert>
#include <vector>
#include "../algebra/Add_Mul.hpp"
#include "../algebra/concepts.hpp"
#include "../util/type_traits.hpp"

template <class R> struct matrix {
  static_assert(semiring<R>);
  using S = typename R::S;

public:
  struct row {
    S& operator[](int j) {
      assert(0 <= j && j < w);
      return d[j];
    }
    const S& operator[](int j) const {
      assert(0 <= j && j < w);
      return d[j];
    }
    void swap(const row& r) {
      assert(w == r.w);
      d.swap(r.d);
    }
    row& operator=(const row& r) {
      assert(w == r.w);
      d = r.d;
    }
    row(int _w) : w(_w), d(_w, R::zero()) {}
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

  friend matrix operator+(const matrix& lhs, const matrix& rhs) {
    assert(lhs.h == rhs.h && lhs.w == rhs.w);
    matrix res(lhs.h, lhs.w);
    for (int i = 0; i < lhs.h; i++) {
      for (int j = 0; j < lhs.w; j++) {
        res[i][j] = R::add(lhs[i][j], rhs[i][j]);
      }
    }
    return res;
  }  
  friend matrix operator*(const matrix& lhs, const matrix& rhs) {
    assert(lhs.w == rhs.h);
    matrix res(lhs.h, rhs.w);
    for (int i = 0; i < lhs.h; i++) {
      for (int k = 0; k < lhs.w; k++) {
        for (int j = 0; j < rhs.w; j++) {
          res[i][j] = R::add(res[i][j], R::mul(lhs[i][k], rhs[k][j]));
        }
      }
    }
    return res;
  }

  matrix operator+=(const matrix& rhs) { return *this = *this + rhs; }  
  matrix operator*=(const matrix& rhs) { return *this = *this * rhs; }

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

private:
  int h, w;
  std::vector<row> d;
};

template <class T>
  requires std::is_arithmetic_v<T> || is_modint_v<T>
struct matrix<T> : matrix<Add_Mul<T>> {
  using matrix<Add_Mul<T>>::matrix;
};
