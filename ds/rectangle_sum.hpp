#pragma once

#include <algorithm>
#include <limits>
#include <vector>

#include "ds/wavelet_matrix.hpp"
#include "util/algo_utility.hpp"
#include "util/coordinate_compression.hpp"

namespace cp {

template <class T, class U> class rectangle_sum {
 public:
  rectangle_sum() {}

  void add_point(T x, T y, U w) {
    xs.push_back(x);
    ys.push_back(y);
    ws.push_back(w);
    n++;
  }

  void init() {
    auto p = sort(xs);
    auto q = inverse(sort(ys));

    wm = wavelet_matrix<bit_size>(n);
    for (int i = 0; i < n; i++) wm.set(i, q[p[i]]);
    wm.init();

    cum.assign(bit_size, std::vector<U>(n + 1));
    for (int i = 0; i < n; i++) {
      for (int k = i, h = bit_size - 1; h >= 0; h--) {
        k = wm.next(h, k);
        cum[h][k + 1] = ws[p[i]];
      }
    }
    for (int h = 0; h < bit_size; h++) {
      for (int i = 0; i < n; i++) {
        cum[h][i + 1] += cum[h][i];
      }
    }
    initialized = true;
  }

  // aggregate `[l, r) * [d, u)`
  U sum(T l, T d, T r, T u) {
    assert(initialized);
    assert(l <= r && d <= u);
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
        ans += cum[h][r0] - cum[h][l0];
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
  wavelet_matrix<bit_size> wm;
  std::vector<std::vector<U>> cum;
  bool initialized = false;
};

}  // namespace cp