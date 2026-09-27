#pragma once

#include <cassert>

#include "ds/fenwick_tree.hpp"

namespace cp {

template <class T> class range_add_range_sum {
 public:
  range_add_range_sum() : n(0) {}
  explicit range_add_range_sum(int _n) : n(_n), fw1(_n + 1), fw2(_n + 1) {}

  // [l, n)
  void add(int l, T w) {
    assert(0 <= l <= n);
    fw1.add(l, w);
    fw2.add(l, w * l);
  }

  void add(int l, int r, T w) {
    assert(0 <= l && l <= r && r <= n);
    add(l, w);
    add(r, -w);
  }

  // [0, r)
  T sum(int r) const {
    assert(0 <= r && r <= n);
    return r * fw1.sum(r) - fw2.sum(r);
  }

  T sum(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    return sum(r) - sum(l);
  }

  int size() const { return n; }

 private:
  int n;
  fenwick_tree<T> fw1, fw2;
};

}  // namespace cp