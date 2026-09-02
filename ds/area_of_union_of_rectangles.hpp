#pragma once

#include <algorithm>
#include <cassert>
#include <limits>

#include "ds/lazy_segtree.hpp"
#include "util/algo_utility.hpp"

namespace cp {

template <class T> class area_of_union_of_rectangles {
 public:
  area_of_union_of_rectangles() {}

  // add [l, r] * [d, u]
  void add_rect(T l, T d, T r, T u) {
    assert(l <= r && d <= u);
    if (l == r || d == u) return;
    x.push_back(l);
    x.push_back(r);
    y.push_back(d);
    y.push_back(u);
  }

  T calc() {
    int n = int(x.size());

    std::vector<int> idx_x = sort(x);
    std::vector<int> idx_y = sort(y);
    std::vector<int> comp_y(n);
    for (int i = 0; i < n; i++) comp_y[idx_y[i]] = i;

    std::vector<S> a(n - 1);
    for (int i = 0; i < n - 1; i++) a[i] = {0, y[i + 1] - y[i]};
    lazy_segtree<S, op, e, T, act, compose, id> seg(a);

    T ans = 0;
    T total = y[n - 1] - y[0];
    for (int i = 0; i < n - 1; i++) {
      int j = idx_x[i] / 2;
      int d = comp_y[2 * j];
      int u = comp_y[2 * j + 1];
      T w = idx_x[i] % 2 ? -1 : 1;
      seg.apply(d, u, w);

      auto [min, cnt] = seg.all_prod();
      T dy = total - (min == 0 ? cnt : 0);
      T dx = x[i + 1] - x[i];
      ans += dx * dy;
    }
    return ans;
  }

 private:
  std::vector<T> x, y;

  // range min, range min count, range add
  struct S {
    T min, cnt;
  };
  static S op(S x, S y) {
    if (x.min == y.min) return {x.min, x.cnt + y.cnt};
    if (x.min < y.min) return {x.min, x.cnt};
    return {y.min, y.cnt};
  }
  static S e() { return {std::numeric_limits<T>::max(), 0}; }
  static S act(T f, S x) { return {x.min + f, x.cnt}; }
  static T compose(T g, T f) { return g + f; }
  static T id() { return 0; }
};

}  // namespace cp