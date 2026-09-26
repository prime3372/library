#pragma once

#include <cassert>

#include "ds/fenwick_tree.hpp"

namespace cp {

template <class T> class range_add_range_sum {
 public:
  range_add_range_sum() : n(0) {}
  explicit range_add_range_sum(int _n) : n(_n), fw1(_n + 1), fw2(_n + 1) {}

  void add(int l, int r, T v) {
    assert(0 <= l && l <= r && r <= n);
    fw1.add(l, v);
    fw1.add(r, -v);
    fw2.add(l, v * l);
    fw2.add(r, -v * r);
  }

  T sum(int r) const {
    assert(0 <= r && r <= n);
    return r * fw1.sum(r) - fw2.sum(r);
  }

  T sum(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    return sum(r) - sum(l);
  }

 private:
  int n;
  fenwick_tree<T> fw1, fw2;
};

}  // namespace cp