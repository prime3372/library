#pragma once

#include <vector>

#include "ds/wavelet-matrix.hpp"
#include "util/coordinate-compression.hpp"

namespace cp {

template <class T, class Compare = std::less<T>, int bit_size = 24>
struct RangeKthSmallest {
 public:
  RangeKthSmallest() {}
  explicit RangeKthSmallest(const std::vector<T>& a) { init(a); }

  void init(const std::vector<T>& a) {
    n = int(a.size());
    wm = WaveletMatrix<bit_size>(n);
    cc.init(a);
    for (int i = 0; i < n; i++) wm.set(i, cc(a[i]));
    wm.init();
    initialized = true;
  }

  const T& query(int l, int r, int k) {
    assert(initialized);
    assert(0 <= l && l <= r && r <= n);
    assert(0 <= k && k < r - l);
    int ans = 0;
    for (int h = bit_size - 1; h >= 0; h--) {
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
  WaveletMatrix<bit_size> wm;
  CoordinateCompression<T, Compare> cc;
  bool initialized = false;
};

}  // namespace cp