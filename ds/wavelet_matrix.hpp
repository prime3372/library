#pragma once

#include <algorithm>
#include <bit>
#include <utility>
#include <vector>

namespace cp {

namespace internal {

struct bit_vector {
public:
  bit_vector() {}
  bit_vector(int _n) : n(_n), block(n / w + 1, 0), count(block.size()) {}

  void set(int i) {
    block[i / w] |= 1LL << (i % w);
  }

  void build() {
    for (int i = 1; i < block.size(); i++) {
      count[i] = count[i - 1] + std::popcount(block[i - 1]);
    }
  }

  bool operator[](int i) const {
    return (block[i / w] & (1ULL << (i % w))) != 0;
  }

  int rank0(int i) const { return i - rank1(i); }
  int rank1(int i) const {
    return count[i / w] + std::popcount(block[i / w] & (1ULL << (i % w)));
  }

  int zeros() { return rank1(n); }

private:
  static constexpr unsigned int w = 64;
  int n;
  std::vector<unsigned long long> block;
  std::vector<int> count;
};

} // namespace internal

template <class T> struct wavelet_matrix {
public:
  wavelet_matrix(int _n) : n(std::max(_n, 1)), a(n) {}
  wavelet_matrix(const vector<T>& _a) : n(_a.size()), a(_a) { build(); }

  void build() {
    log = std::bit_width(std::max<T>(*std::max_element(a.begin(), a.end()), 1));
    bv.assign(log, n);
    vector<T> cur = a, nxt(n);
    for (int h = log - 1; h >= 0; --h) {
      for (int i = 0; i < n; ++i) {
        if ((cur[i] >> h) & 1) bv[h].set(i);
      }
      bv[h].build();
      array<decltype(begin(nxt)), 2> it{begin(nxt), begin(nxt) + bv[h].zeros};
      for (int i = 0; i < n; ++i) *it[bv[h].get(i)]++ = cur[i];
      swap(cur, nxt);
    }
  }

  void set(unsigned int i, const T& x) { 
    assert(x >= 0);
    a[i] = x; 
  }

  std::pair<unsigned int, unsigned int> succ0(int l, int r, int h) const {
    return make_pair(bv[h].rank0(l), bv[h].rank0(r));
  }

  std::pair<unsigned int, unsigned int> succ1(int l, int r, int h) const {
    unsigned int l0 = bv[h].rank0(l);
    unsigned int r0 = bv[h].rank0(r);
    unsigned int zeros = bv[h].zeros();
    return make_pair(l + zeros - l0, r + zeros - r0);
  }

  // return a[k]
  T access(unsigned int k) const {
    T ret = 0;
    for (int h = log - 1; h >= 0; --h) {
      unsigned int f = bv[h].get(k);
      ret |= f ? T(1) << h : 0;
      k = f ? bv[h].rank1(k) + bv[h].zeros : bv[h].rank0(k);
    }
    return ret;
  }

  // k-th (0-indexed) smallest number in a[l, r)
  T kth_smallest(unsigned int l, unsigned int r, unsigned int k) const {
    T res = 0;
    for (int h = log - 1; h >= 0; --h) {
      unsigned int l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
      if (k < r0 - l0)
        l = l0, r = r0;
      else {
        k -= r0 - l0;
        res |= (T)1 << h;
        l += bv[h].zeros - l0;
        r += bv[h].zeros - r0;
      }
    }
    return res;
  }

  // k-th (0-indexed) largest number in a[l, r)
  T kth_largest(int l, int r, int k) {
    return kth_smallest(l, r, r - l - k - 1);
  }

  // count i s.t. (l <= i < r) && (v[i] < upper)
  int range_freq(int l, int r, T upper) {
    if (upper >= (T(1) << log)) return r - l;
    int ret = 0;
    for (int h = log - 1; h >= 0; --h) {
      bool f = (upper >> h) & 1;
      unsigned int l0 = bv[h].rank0(l), r0 = bv[h].rank0(r);
      if (f) {
        ret += r0 - l0;
        l += bv[h].zeros - l0;
        r += bv[h].zeros - r0;
      } else {
        l = l0;
        r = r0;
      }
    }
    return ret;
  }

  int range_freq(int l, int r, T lower, T upper) {
    return range_freq(l, r, upper) - range_freq(l, r, lower);
  }

  // max v[i] s.t. (l <= i < r) && (v[i] < upper)
  T prev_value(int l, int r, T upper) {
    int cnt = range_freq(l, r, upper);
    return cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);
  }

  // min v[i] s.t. (l <= i < r) && (lower <= v[i])
  T next_value(int l, int r, T lower) {
    int cnt = range_freq(l, r, lower);
    return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);
  }

private:
  int n, log;
  vector<T> a;
  vector<internal::bit_vector> bv;
};

} // namespace cp