#pragma once

#include <cassert>

#include "ds/dynamic_fenwick_tree.hpp"

namespace cp {

template <class T> class dynamic_range_add_range_sum {
  using ull = unsigned long long;

 public:
  dynamic_range_add_range_sum() : n(0) {}
  explicit dynamic_range_add_range_sum(ull _n)
      : n(_n), fw1(_n + 1), fw2(_n + 1) {}

  void add(ull l, ull r, T w) {
    assert(0 <= l && l <= r && r <= n);
    add(l, w);
    add(r, -w);
  }

  T sum(ull l, ull r) const {
    assert(0 <= l && l <= r && r <= n);
    return sum(r) - sum(l);
  }

  ull size() const { return n; }

 private:
  ull n;
  dynamic_fenwick_tree<T> fw1, fw2;

  // [l, n)
  T add(ull l) {
    fw1.add(l, w);
    fw2.add(l, w * T(l));
  }
  // [0, r)
  T sum(ull r) const {
    assert(0 <= r && r <= n);
    return fw1.sum(r) * T(r) - fw2.sum(r);
  }
};

}  // namespace cp