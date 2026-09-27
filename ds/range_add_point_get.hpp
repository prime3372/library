#pragma once

#include <cassert>

#include "ds/fenwick_tree.hpp"

namespace cp {

template <class T> class range_add_point_get {
 public:
  range_add_point_get() : n(0) {}
  explicit range_add_point_get(int _n) : n(_n), fw(_n) {}

  void add(int l, int r, T v) {
    assert(0 <= l && l <= r && r <= n);
    if (l < n) fw.add(l, v);
    if (r < n) fw.add(r, -v);
  }

  T operator[](int i) const {
    assert(0 <= i && i < n);
    return fw.sum(i + 1);
  }

  int size() const { return n; }

 private:
  int n;
  fenwick_tree<T> fw;
};

}  // namespace cp