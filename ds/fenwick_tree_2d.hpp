#pragma once

#include <cassert>
#include <iostream>
#include <vector>

#include "ds/fenwick_tree.hpp"

namespace cp {

template <class T> class fenwick_tree_2d {
 public:
  fenwick_tree_2d() : n(0), m(0) {}
  explicit fenwick_tree_2d(int _n, int _m)
      : n(_n), m(_m), fw(_n, fenwick_tree<T>(m)) {}

  void add(int i, int j, T w) {
    assert(0 <= i && i < n);
    assert(0 <= j && j < m);
    i++;
    while (i <= n) {
      fw[i - 1].add(j, w);
      i += i & -i;
    }
  }

  class ref {
   public:
    T operator[](int j) const {
      assert(0 <= j && j < ptr->m);
      return ptr->sum(i, j, i + 1, j + 1);
    }
    ref(const fenwick_tree_2d* _ptr, int _i) : ptr(_ptr), i(_i) {}

   private:
    const fenwick_tree_2d* ptr;
    int i;
  };

  ref operator[](int i) const {
    assert(0 <= i && i < n);
    return ref(this, i);
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

  friend std::ostream& operator<<(std::ostream& os, const fenwick_tree_2d& fw) {
    for (int i = 0; i < fw.n; i++) {
      for (int j = 0; j < fw.m; j++) {
        os << fw[i][j];
        if (j != fw.m - 1) os << " ";
      }
      if (i != fw.n - 1) os << "\n";
    }
    return os;
  }

 private:
  int n, m;
  std::vector<fenwick_tree<T>> fw;
};

}  // namespace cp