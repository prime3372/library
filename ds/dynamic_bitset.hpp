#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace cp {

class dynamic_bitset {
  using bs = dynamic_bitset;
  using ull = unsigned long long;

 public:
  dynamic_bitset() : n(0) {}
  explicit dynamic_bitset(int _n) : n(_n), a((_n + w - 1) / w) {}
  explicit dynamic_bitset(const std::vector<bool>& v)
      : n(int(v.size())), a((int(v.size()) + w - 1) / w) {
    for (int i = 0; i < n; i++) a[i / w] |= ull(v[i]) << (i % w);
  }

  class ref {
   public:
    operator bool() const { return (*d & mask(pos)) != 0; }
    ref& flip() {
      *d ^= mask(pos);
      return *this;
    }
    ref& operator=(bool x) {
      if (x) {
        *d |= mask(pos);
      } else {
        *d &= ~mask(pos);
      }
      return *this;
    }
    ref& operator=(const ref& other) { return *this = bool(other); }
    ref(bs& b, int i) {
      d = b.a.data() + i / w;
      pos = i % w;
    }

   private:
    ull* d;
    int pos;
  };

  ref operator[](int i) {
    assert(0 <= i && i < n);
    return ref(*this, i);
  }
  bool operator[](int i) const {
    assert(0 <= i && i < n);
    return (a[i / w] & mask(i % w)) != 0;
  }

  bs& flip() {
    if (n == 0) return *this;
    for (int i = 0; i < int(a.size()); i++) {
      a[i] = ~a[i];
    }
    if (n % w) a.back() &= mask(n % w) - 1;
    return *this;
  }
  bs operator~() const { return bs(*this).flip(); }

  int count() const {
    int res = 0;
    for (int i = 0; i < int(a.size()); i++) {
      res += std::popcount(a[i]);
    }
    return res;
  }

  // @param l `0 <= l <= size()`
  // @return max `r` s.t. `l <= r <= size() && (*this)[l]+...+(*this)[r-1] == 0`
  int next(int l) const {
    assert(0 <= l && l <= n);
    if (l == n) return n;
    int i = l / w;
    ull start = a[i];
    start &= -1ULL << (l % w);
    if (start) return i * w + std::countr_zero(start);
    while (++i < int(a.size())) {
      if (a[i]) return i * w + std::countr_zero(a[i]);
    }
    return n;
  }

  // @param r `0 <= r <= size()`
  // @return min `l` s.t. `0 <= l <= r && (*this)[l]+...+(*this)[r-1] == 0`
  int prev(int r) const {
    assert(0 <= r && r <= n);
    if (r == 0) return 0;
    int i = (r - 1) / w;
    ull start = a[i];
    start &= -1ULL >> (w - 1 - ((r - 1) % w));
    if (start) return i * w + (w - std::countl_zero(start));
    while (--i >= 0) {
      if (a[i]) return i * w + (w - std::countl_zero(a[i]));
    }
    return 0;
  }

  int size() const { return n; }

  bs& operator^=(const bs& rhs) {
    assert(n == rhs.n);
    for (int i = 0; i < int(a.size()); i++) {
      a[i] ^= rhs.a[i];
    }
    return *this;
  }
  bs& operator|=(const bs& rhs) {
    assert(n == rhs.n);
    for (int i = 0; i < int(a.size()); i++) {
      a[i] |= rhs.a[i];
    }
    return *this;
  }
  bs& operator&=(const bs& rhs) {
    assert(n == rhs.n);
    for (int i = 0; i < int(a.size()); i++) {
      a[i] &= rhs.a[i];
    }
    return *this;
  }

  bs& operator<<=(int shift) {
    assert(0 <= shift);
    if (n == 0) return *this;
    if (shift >= n) {
      std::fill(a.begin(), a.end(), 0);
      return *this;
    }

    int block_shift = shift / w;
    if (block_shift > 0) {
      for (int i = int(a.size()) - 1; i >= block_shift; i--) {
        a[i] = a[i - block_shift];
      }
      std::fill(a.begin(), a.begin() + block_shift, 0);
    }

    int bit_shift = shift % w;
    if (bit_shift > 0) {
      for (int i = int(a.size()) - 1; i > block_shift; i--) {
        a[i] <<= bit_shift;
        a[i] |= a[i - 1] >> (w - bit_shift);
      }
      a[block_shift] <<= bit_shift;
    }

    if (n % w) a.back() &= mask(n % w) - 1;
    return *this;
  }

  bs& operator>>=(int shift) {
    assert(0 <= shift);
    if (n == 0) return *this;
    if (shift >= n) {
      std::fill(a.begin(), a.end(), 0);
      return *this;
    }

    int block_shift = shift / w;
    if (block_shift > 0) {
      for (int i = 0; i < int(a.size()) - block_shift; i++) {
        a[i] = a[i + block_shift];
      }
      std::fill(a.end() - block_shift, a.end(), 0);
    }

    int bit_shift = shift % w;
    if (bit_shift > 0) {
      for (int i = 0; i < int(a.size()) - block_shift - 1; i++) {
        a[i] >>= bit_shift;
        a[i] |= a[i + 1] << (w - bit_shift);
      }
      a[a.size() - block_shift - 1] >>= bit_shift;
    }

    return *this;
  }

  friend bs operator^(const bs& lhs, const bs& rhs) { return bs(lhs) ^= rhs; }
  friend bs operator|(const bs& lhs, const bs& rhs) { return bs(lhs) |= rhs; }
  friend bs operator&(const bs& lhs, const bs& rhs) { return bs(lhs) &= rhs; }
  friend bs operator<<(const bs& lhs, int shift) { return bs(lhs) <<= shift; }
  friend bs operator>>(const bs& lhs, int shift) { return bs(lhs) >>= shift; }

  friend bool operator==(const bs& lhs, const bs& rhs) {
    return lhs.n == rhs.n && lhs.a == rhs.a;
  }
  friend bool operator!=(const bs& lhs, const bs& rhs) { return !(lhs == rhs); }

  friend std::ostream& operator<<(std::ostream& os, const bs& s) {
    for (int i = 0; i < s.n; i++) os << s[i];
    return os;
  }

 private:
  static constexpr int w = 64;
  int n;
  std::vector<ull> a;

  static ull mask(int pos) { return 1ULL << pos; }
};

}  // namespace cp