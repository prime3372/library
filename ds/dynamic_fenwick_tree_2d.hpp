#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>

#include "ds/dynamic_fenwick_tree.hpp"

namespace cp {

template <class T> class dynamic_fenwick_tree_2d {
  using ull = unsigned long long;

 public:
  dynamic_fenwick_tree_2d() : n(0), m(0) {}
  explicit dynamic_fenwick_tree_2d(int _n, ull _m)
      : n(_n), m(_m), fw(_n, dynamic_fenwick_tree<T>(_m)) {}

  void add(int i, ull j, T x) {
    assert(0 <= i && i < n);
    assert(j < m);
    i++;
    while (i <= n) {
      fw[i - 1].add(j, x);
      i += i & -i;
    }
  }

  class ref {
   public:
    T operator[](ull j) const {
      assert(j < ptr->m);
      return ptr->sum(i, j, i + 1, j + 1);
    }
    ref(const dynamic_fenwick_tree_2d* _ptr, int _i) : ptr(_ptr), i(_i) {}

   private:
    const dynamic_fenwick_tree_2d* ptr;
    int i;
  };

  ref operator[](int i) const {
    assert(0 <= i && i < n);
    return ref(this, i);
  }

  T sum(int l, ull d, int r, ull u) const {
    assert(0 <= l && l <= r && r <= n);
    assert(d <= u && u <= m);
    return sum(r, u) - sum(r, d) - sum(l, u) + sum(l, d);
  }

  T sum(int r, ull u) const {
    assert(0 <= r && r <= n);
    assert(u <= m);
    T s = 0;
    while (r) {
      s += fw[r - 1].sum(u);
      r -= r & -r;
    }
    return s;
  }

  void imos_add(int l, ull d, int r, ull u, T x) {
    assert(0 <= l && l <= r && r <= n);
    assert(d <= u && u <= m);
    if (l < n && d < m) add(l, d, x);
    if (l < n && u < m) add(l, u, -x);
    if (r < n && d < m) add(r, d, -x);
    if (r < n && u < m) add(r, u, x);
  }

  T imos_get(int i, ull j) const {
    assert(0 <= i && i < n);
    assert(j < m);
    return sum(i + 1, j + 1);
  }

  friend std::ostream& operator<<(std::ostream& os,
                                  const dynamic_fenwick_tree_2d& fw) {
    for (int i = 0; i < fw.n; i++) {
      for (ull j = 0; j < fw.m; j++) {
        os << fw[i][j];
        if (j != fw.m - 1) os << " ";
      }
      if (i != fw.n - 1) os << "\n";
    }
    return os;
  }

 private:
  int n;
  ull m;
  std::vector<dynamic_fenwick_tree<T>> fw;
};

}  // namespace cp