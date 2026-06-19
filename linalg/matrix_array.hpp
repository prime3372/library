#pragma once

#include <array>
#include <cassert>
#include "../algebra/Add_Mul.hpp"
#include "../algebra/semiring.hpp"
#include "../util/type_traits.hpp"

namespace internal {

template <class R, int w>
struct row {
  using S = typename R::S;
public:
  S& operator[](int j) {
    assert(0 <= j && j < w);
    return d[j];
  }
  const S& operator[](int j) const {
    assert(0 <= j && j < w);
    return d[j];
  }
  void swap(const row& r) {
    d.swap(r.d);
  }
  row& operator=(const row& r) {
    d = r.d;
    return *this;
  }
  row() : d{} {
    std::fill(d.begin(), d.end(), R::zero());
  }
private:
  std::array<S, w> d;
};

} // namespace internal

template <class R, int h, int w> struct matrix_array {
  static_assert(semiring<R>);
  using S = typename R::S;

  matrix_array() : d{} {
    std::fill(d.begin(), d.end(), internal::row<R, w>());
  }

  constexpr int height() const { return h; }
  constexpr int width() const { return w; }

  internal::row<R, w>& operator[](int i) {
    assert(0 <= i && i < h);
    return d[i];
  }
  const internal::row<R, w>& operator[](int i) const {
    assert(0 <= i && i < h);
    return d[i];
  }

  friend matrix_array operator+(const matrix_array& lhs, const matrix_array& rhs) {
    matrix_array res;
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        res[i][j] = R::add(lhs[i][j], rhs[i][j]);
      }
    }
    return res;
  }

  matrix_array& operator+=(const matrix_array& rhs) { return *this = *this + rhs; }
  matrix_array& operator*=(const matrix_array<R, w, w>& rhs) { return *this = *this * rhs; }

  template <int n> static matrix_array<R, n, n> unit() {
    matrix_array<R, n, n> res;
    for (int i = 0; i < n; i++) res[i][i] = R::one();
    return res;
  }

  matrix_array pow(long long n) const {
    static_assert(h == w);
    assert(0 <= n);
    matrix_array r = unit<h>(), mat = *this;
    while (n) {
      if (n & 1) r *= mat;
      mat *= mat;
      n >>= 1;
    }
    return r;
  }

private:
  std::array<internal::row<R, w>, h> d;
};

template <semiring R, int l, int m, int n>
matrix_array<R, l, n> operator*(const matrix_array<R, l, m>& lhs,
                                const matrix_array<R, m, n>& rhs) {
  matrix_array<R, l, n> res;
  for (int i = 0; i < l; i++) {
    for (int k = 0; k < m; k++) {
      for (int j = 0; j < n; j++) {
        res[i][j] = R::add(res[i][j], R::mul(lhs[i][k], rhs[k][j]));
      }
    }
  }
  return res;
}

template <class T, int h, int w>
  requires std::is_arithmetic_v<T> || is_modint_v<T>
struct matrix_array<T, h, w> : matrix_array<Add_Mul<T>, h, w> {
  using matrix_array<Add_Mul<T>, h, w>::matrix_array;
};

template <class T, int h, int w>
struct is_matrix<matrix_array<T, h, w>> : std::true_type {};
