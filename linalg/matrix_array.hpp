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
private:
  using R = std::conditional_t<semiring<T>, T, add_mul<T>>;
  using S = typename R::S;

public:
  matrix_array() : d{} {
    d.fill(std::array<S, w>{});
  }

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

  static matrix_array unit() requires (h == w) {
    matrix_array res;
    for (int i = 0; i < h; i++) res[i][i] = R::one();
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

template <class T, int h, int w>
struct is_matrix<matrix_array<T, h, w>> : std::true_type {};

} // namespace cp