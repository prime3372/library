#pragma once

#include <vector>

#include "ds/wavelet_matrix.hpp"
#include "util/coordinate_compression.hpp"

namespace cp {

template <class T> class range_kth_smallest {
 public:
  range_kth_smallest() {}
  explicit range_kth_smallest(const std::vector<T>& a) { init(a); }

  void init(const std::vector<T>& a) {
    n = int(a.size());
    wm = wavelet_matrix<32>(n);
    cc.init(a);
    for (int i = 0; i < n; i++) {
      wm.set(i, cc(a[i]));
    }
    wm.init();
    initialized = true;
  }

  const T& query(int l, int r, int k) {
    assert(initialized);
    assert(0 <= l && l <= r && r <= n);
    assert(0 <= k && k < r - l);
    int ans = 0;
    for (int h = 31; h >= 0; h--) {
      int l0 = wm.next0(h, l);
      int r0 = wm.next0(h, r);
      if (r0 - l0 > k) {
        l = l0;
        r = r0;
      } else {
        ans += 1 << h;
        k -= r0 - l0;
        l = wm.next1(h, l);
        r = wm.next1(h, r);
      }
    }
    return cc[ans];
  }

 private:
  int n = 0;
  wavelet_matrix<32> wm;
  coordinate_compression<T> cc;
  bool initialized = false;
};

}  // namespace cp