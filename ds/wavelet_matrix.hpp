#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <utility>
#include <vector>

#include "ds/bit_vector.hpp"
#include "util/type_traits.hpp"

namespace cp {

class wavelet_matrix {
  using ull = unsigned long long;

 public:
  wavelet_matrix() : wavelet_matrix(0) {}
  explicit wavelet_matrix(int _n) : n(_n), a(_n) {}

  void set(int i, ull x) {
    assert(0 <= i && i < n);
    a[i] = x;
  }

  void build() {
    if (n == 0) return;
    ull max_a = *std::max_element(a.begin(), a.end());
    log = max_a ? std::bit_width(max_a) : 1;

    bv.assign(log, bit_vector(n));
    std::vector<ull> cur = a, nxt(n);
    for (int h = log - 1; h >= 0; h--) {
      for (int i = 0; i < n; i++) {
        if ((cur[i] >> h) & 1) bv[h].set(i);
      }
      bv[h].build();
      std::array itr = {nxt.begin(), nxt.begin() + bv[h].zeros()};
      for (int i = 0; i < n; i++) *(itr[bv[h][i]]++) = cur[i];
      std::swap(cur, nxt);
    }
    initialized = true;
  }

  ull operator[](int k) const {
    assert(0 <= k && k < n);
    return a[k];
  }

  ull kth_smallest(int l, int r, int k) const {
    assert(initialized);
    assert(0 <= l && l <= r && r <= n);
    assert(0 <= k && k < r - l);
    ull ans = 0;
    for (int h = log - 1; h >= 0; h--) {
      int l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
      if (k < r0 - l0) {
        l = l0;
        r = r0;
      } else {
        k -= r0 - l0;
        ans |= ull(1) << h;
        l += bv[h].zeros() - l0;
        r += bv[h].zeros() - r0;
      }
    }
    return ans;
  }

  ull kth_largest(int l, int r, int k) {
    return kth_smallest(l, r, r - l - k - 1);
  }

  int range_freq(int l, int r, ull upper) {
    assert(initialized);
    assert(0 <= l && l <= r && r <= n);
    int ans = 0;
    for (int h = log - 1; h >= 0; h--) {
      bool f = (upper >> h) & 1;
      int l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
      if (f) {
        ans += r0 - l0;
        l = bv[h].zeros() - l0;
        r += bv[h].zeros() - r0;
      } else {
        l = l0;
        r = r0;
      }
    }
    return ans;
  }

  int range_freq(int l, int r, ull lower, ull upper) {
    return range_freq(l, r, upper) - range_freq(l, r, lower);
  }

 private:
  int n, log;
  bool initialized = false;
  std::vector<ull> a;
  std::vector<bit_vector> bv;
};

}  // namespace cp