#pragma once

#include <cassert>

#include "ds/fenwick-tree.hpp"

namespace cp {

template <class T> struct RangeAddRangeSum {
 public:
  RangeAddRangeSum() : n(0) {}
  explicit RangeAddRangeSum(int _n) : n(_n), fw1(_n + 1), fw2(_n + 1) {}
  void add(int l, int r, T w) {
    assert(0 <= l && l <= r && r <= n);
    add(l, w);
    add(r, -w);
  }
  T sum(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    return sum(r) - sum(l);
  }
  int size() const { return n; }

 private:
  int n;
  FenwickTree<T> fw1, fw2;

  // [l, n)
  void add(int l, T w) {
    fw1.add(l, w);
    fw2.add(l, w * T(l));
  }
  // [0, r)
  T sum(int r) const { return fw1.sum(r) * T(r) - fw2.sum(r); }
};

}  // namespace cp