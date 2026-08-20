#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

#include "util/type_traits.hpp"

namespace cp {

namespace internal {

class bit_vector {
 public:
  bit_vector() {}
  explicit bit_vector(int _n) : n(_n), block(n / w + 1), count(n / w + 1) {}

  void set(int i) { block[i / w] |= 1LL << (i % w); }
  void build() {
    for (int i = 1; i < int(block.size()); i++) {
      count[i] = count[i - 1] + std::popcount(block[i - 1]);
    }
  }

  bool operator[](int i) const {
    return (block[i / w] & (1ULL << (i % w))) != 0;
  }
  int rank0(int i) const { return i - rank1(i); }
  int rank1(int i) const {
    return count[i / w] + std::popcount(block[i / w] & ((1ULL << (i % w)) - 1));
  }
  int zeros() const { return rank0(n); }

 private:
  static constexpr int w = 64;
  int n;
  std::vector<unsigned long long> block;
  std::vector<int> count;
};

}  // namespace internal

template <class T> requires internal::is_unsigned_int_v<T>
class wavelet_matrix {
 public:
  wavelet_matrix() : wavelet_matrix(0) {}
  explicit wavelet_matrix(int _n) : n(_n), a(_n) {}
  explicit wavelet_matrix(const std::vector<T>& _a) : n(_a.size()), a(_a) {
    build();
  }

  void set(int i, const T& x) {
    assert(0 <= i && i < n);
    a[i] = x;
  }

  void build() {
    if (n == 0) return;
    bv.assign(log, internal::bit_vector(n));
    std::vector<T> cur = a, nxt(n);
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

  T operator[](int k) const {
    assert(0 <= k && k < n);
    return a[k];
  }

  T kth_smallest(int l, int r, int k) const {
    assert(initialized);
    assert(0 <= l && l <= r && r <= n);
    assert(0 <= k && k < r - l);
    T ans = 0;
    for (int h = log - 1; h >= 0; h--) {
      int l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
      if (k < r0 - l0) {
        l = l0;
        r = r0;
      } else {
        k -= r0 - l0;
        ans |= T(1) << h;
        l += bv[h].zeros() - l0;
        r += bv[h].zeros() - r0;
      }
    }
    return ans;
  }

  T kth_largest(int l, int r, int k) {
    return kth_smallest(l, r, r - l - k - 1);
  }

  int range_freq(int l, int r, T upper) {
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

  int range_freq(int l, int r, T lower, T upper) {
    return range_freq(l, r, upper) - range_freq(l, r, lower);
  }

 private:
  static constexpr int log = std::numeric_limits<T>::digits;
  int n;
  bool initialized = false;
  std::vector<T> a;
  std::vector<internal::bit_vector> bv;
};

}  // namespace cp