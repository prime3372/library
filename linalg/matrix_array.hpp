#pragma once

#include <array>
#include <cassert>
#include <type_traits>

#include "algebra/add_mul.hpp"
#include "algebra/semiring.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class T, int h, int w>
  requires (semiring<T> || std::is_arithmetic_v<T> || is_modint_v<T>)
struct matrix_array {
public:
  using R = std::conditional_t<semiring<T>, T, add_mul<T>>;
  using S = typename R::S;

  matrix_array() : d{} { d.fill(std::array<S, w>{}); }

  constexpr int height() const { return h; }
  constexpr int width() const { return w; }

  std::array<S, w>& operator[](int i) {
    assert(0 <= i && i < h);
    return d[i];
  }
  const std::array<S, w>& operator[](int i) const {
    assert(0 <= i && i < h);
    return d[i];
  }

  matrix_array& operator+=(const matrix_array& rhs) {
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        (*this)[i][j] = R::add((*this)[i][j], rhs[i][j]);
      }
    }
    return *this;
  }

  matrix_array& operator*=(const S& rhs) {
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        (*this)[i][j] = R::mul((*this)[i][j], rhs);
      }
    }
    return *this;
  }

  friend matrix_array operator+(const matrix_array& lhs,
                                const matrix_array& rhs) {
    return matrix_array(lhs) += rhs;
  }
  friend matrix_array operator*(const matrix_array& lhs,
                                const S& rhs) {
    return matrix_array(lhs) *= rhs;
  }
  friend matrix_array operator*(const S& lhs,
                                const matrix_array& rhs) {
    return matrix_array(rhs) *= lhs;
  }

  matrix_array& operator*=(const matrix_array<R, w, w>& rhs) { return *this = *this * rhs; }

  template <int n> static matrix_array<T, n, n> unit() {
    matrix_array<T, n, n> res;
    for (int i = 0; i < n; i++) res[i][i] = R::one();
    return res;
  }

  matrix_array pow(long long n) requires (h == w) const {
    assert(0 <= n);
    matrix_array r = unit<h>(), mat = *this;
    while (n) {
      if (n & 1) r *= mat;
      mat *= mat;
      n >>= 1;
    }
    return r;
  }

  friend std::istream& operator>>(std::istream& is, matrix_array& mat) {
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        is >> mat[i][j];
      }
    }
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, matrix_array& mat) {
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        os << mat[i][j] << " ";
      }
      if (i != mat.height) os << "\n";
    }
    return os;
  }

private:
  std::array<std::array<S, w>, h> d;
};

template <class T, int l, int m, int n>
matrix_array<T, l, n> operator*(const matrix_array<T, l, m>& lhs,
                                const matrix_array<T, m, n>& rhs) {
  using R = matrix_array<T, l, n>::R;
  matrix_array<T, l, n> res;
  for (int i = 0; i < l; i++) {
    for (int k = 0; k < m; k++) {
      for (int j = 0; j < n; j++) {
        res[i][j] = R::add(res[i][j], R::mul(lhs[i][k], rhs[k][j]));
      }
    }
  }
  return res;
}

} // namespace cp