#pragma once

#include <algorithm>
#include <limits>
#include <vector>

#include "ds/fenwick_tree.hpp"
#include "ds/wavelet_matrix.hpp"
#include "util/algo_utility.hpp"

namespace cp {

template <class T, class U> class offline_point_add_rectangle_sum {
 public:
  offline_point_add_rectangle_sum() {}

  void add_point(T x, T y, U w = 0) {
    xs.push_back(x);
    ys.push_back(y);
    ws.push_back(w);
    n++;
  }

  void init() {
    auto p = sort(xs);

    points.resize(n);
    for (int i = 0; i < n; i++) {
      points[i] = {xs[i], ys[p[i]], i};
    }
    sort(points.begin(), points.end());

    auto comp = inverse(sort(ys));

    wm = wavelet_matrix<bit_size>(n);
    for (int i = 0; i < n; i++) wm.set(i, comp[p[i]]);
    wm.init();

    fw.assign(bit_size, fenwick_tree<U>(n + 1));
    for (int i = 0; i < n; i++) {
      int k = i;
      for (int h = bit_size - 1; h >= 0; h--) {
        k = wm.next(h, k);
        fw[h].add(k, ws[p[i]]);
      }
    }
    initialized = true;
  }

  void add(T x, T y, U w) {
    auto lb = std::lower_bound(points.begin(), points.end(),
                               std::make_tuple(x, y, U(0)));
    assert(lb != points.end());
    auto [x2, y2, i] = *lb;
    assert(x == x2 && y == y2);
    for (int k = i, h = bit_size - 1; h >= 0; h--) {
      k = wm.next(h, k);
      fw[h].add(k, w);
    }
  }

  U sum(T l, T d, T r, T u) {
    assert(initialized);
    return lower_sum(l, r, u) - lower_sum(l, r, d);
  }

  U lower_sum(T l, T r, T u) {
    int left = int(std::lower_bound(xs.begin(), xs.end(), l) - xs.begin());
    int right = int(std::lower_bound(xs.begin(), xs.end(), r) - xs.begin());
    int upper = int(std::lower_bound(ys.begin(), ys.end(), u) - ys.begin());
    U ans = 0;
    for (int h = bit_size - 1; h >= 0; h--) {
      int l0 = wm.next0(h, left);
      int r0 = wm.next0(h, right);
      if ((upper >> h) & 1) {
        ans += fw[h].sum(l0, r0);
        left = wm.next1(h, left);
        right = wm.next1(h, right);
      } else {
        left = l0;
        right = r0;
      }
    }
    return ans;
  }

 private:
  static constexpr int bit_size = 32;
  int n = 0;
  std::vector<T> xs, ys;
  std::vector<U> ws;
  std::vector<std::tuple<T, T, int>> points;
  wavelet_matrix<bit_size> wm;
  std::vector<fenwick_tree<U>> fw;
  bool initialized = false;
};

}  // namespace cp