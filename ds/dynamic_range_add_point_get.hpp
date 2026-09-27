#pragma once

#include <cassert>

#include "ds/dynamic_fenwick_tree.hpp"

namespace cp {

template <class T> class dynamic_range_add_point_get {
 public:
  dynamic_range_add_point_get() : n(0) {}
  explicit dynamic_range_add_point_get(ull _n) : n(_n), fw(_n) {}

  void add(ull l, ull r, T w) {
    assert(0 <= l && l <= r && r <= n);
    if (l < n) fw.add(l, w);
    if (r < n) fw.add(r, -w);
  }

  T operator[](ull i) const {
    assert(0 <= i && i < n);
    return fw.sum(i + 1);
  }

  ull size() const { return n; }

 private:
  ull n;
  dynamic_fenwick_tree<T> fw;
};

}  // namespace cp