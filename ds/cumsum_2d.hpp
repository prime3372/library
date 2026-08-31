#pragma once

#include <cassert>
#include <iostream>
#include <vector>

namespace cp {

template <class T> class cumsum_2d {
 public:
  cumsum_2d() : n(0), m(0) {}
  explicit cumsum_2d(int _n, int _m)
      : n(_n), m(_m), val(_n, std::vector<T>(_m)) {}
  explicit cumsum_2d(int _n, int _m, const T& x)
      : n(_n), m(_m), val(_n, std::vector<T>(_m, x)) {}

  void accumulate() {
    cum.resize(n + 1, std::vector<T>(m + 1));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cum[i + 1][j + 1] = cum[i + 1][j] + val[i][j];
      }
    }
    for (int j = 0; j < m; j++) {
      for (int i = 0; i < n; i++) {
        cum[i + 1][j + 1] += cum[i][j + 1];
      }
    }
    accumulated = true;
  }

  std::vector<T>& operator[](int i) {
    assert(0 <= i && i < n);
    return val[i];
  }
  const std::vector<T>& operator[](int i) const {
    assert(0 <= i && i < n);
    return val[i];
  }

  T sum(int r, int u) {
    assert(0 <= r && r <= n);
    assert(0 <= u && u <= m);
    if (!accumulated) accumulate();
    return cum[r][u];
  }

  T sum(int l, int d, int r, int u) {
    assert(0 <= l && l <= r && r <= n);
    assert(0 <= d && d <= u && u <= m);
    if (!accumulated) accumulate();
    return cum[r][u] - cum[r][d] - cum[l][u] + cum[l][d];
  }

  void imos_add(int l, int d, int r, int u, T x) {
    assert(0 <= l && l <= r && r <= n);
    assert(0 <= d && d <= u && u <= m);
    if (l < n && d < m) val[l][d] += x;
    if (l < n && u < m) val[l][u] -= x;
    if (r < n && d < m) val[r][d] -= x;
    if (r < n && u < m) val[r][u] += x;
  }

  T imos_get(int i, int j) {
    assert(0 <= i && i < n);
    assert(0 <= j && j < m);
    return sum(i + 1, j + 1);
  }

  friend std::ostream& operator<<(std::ostream& os, const cumsum_2d& sum) {
    for (int i = 0; i < sum.n; i++) {
      for (int j = 0; j < sum.m; j++) {
        os << sum[i][j];
        if (j != sum.m - 1) os << " ";
      }
      if (i != sum.n - 1) os << "\n";
    }
    return os;
  }

 private:
  int n, m;
  bool accumulated = false;
  std::vector<std::vector<T>> val;
  std::vector<std::vector<T>> cum;
};

}  // namespace cp