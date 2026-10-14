#pragma once

#include <cassert>
#include <utility>
#include <vector>

#include "ds/fenwick-tree.hpp"

namespace cp {

template <class T> struct FenwickTree2D {
 public:
  FenwickTree2D() : n(0), m(0) {}
  explicit FenwickTree2D(int _n, int _m)
      : n(_n), m(_m), fw(_n, FenwickTree<T>(m)) {}

  void add(int i, int j, T w) {
    assert(0 <= i && i < n);
    assert(0 <= j && j < m);
    i++;
    while (i <= n) {
      fw[i - 1].add(j, w);
      i += i & -i;
    }
  }

  T sum(int l, int d, int r, int u) const {
    assert(0 <= l && l <= r && r <= n);
    assert(0 <= d && d <= u && u <= m);
    return sum(r, u) - sum(r, d) - sum(l, u) + sum(l, d);
  }

  T sum(int r, int u) const {
    assert(0 <= r && r <= n);
    assert(0 <= u && u <= m);
    T res = 0;
    while (r) {
      res += fw[r - 1].sum(u);
      r -= r & -r;
    }
    return res;
  }

  void imos_add(int l, int d, int r, int u, T x) {
    assert(0 <= l && l <= r && r <= n);
    assert(0 <= d && d <= u && u <= m);
    if (l < n && d < m) add(l, d, x);
    if (l < n && u < m) add(l, u, -x);
    if (r < n && d < m) add(r, d, -x);
    if (r < n && u < m) add(r, u, x);
  }

  T imos_get(int i, int j) const {
    assert(0 <= i && i < n);
    assert(0 <= j && j < m);
    return sum(i + 1, j + 1);
  }

  std::pair<int, int> size() { return {n, m}; }

 private:
  int n, m;
  std::vector<FenwickTree<T>> fw;
};

}  // namespace cp