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

 public:
  dynamic_bitset() : n(0) {}
  explicit dynamic_bitset(int _n) : n(_n), a((_n + w - 1) / w, 0) {}
  explicit dynamic_bitset(int _n, bool b)
      : n(_n), a((_n + w - 1) / w, b ? -1 : 0) {
    if (b && n % w) a.back() &= mask(n % w) - 1;
  }
  explicit dynamic_bitset(const std::string& s)
      : n(int(s.size())), a((int(s.size()) + w - 1) / w) {
    for (int i = 0; i < n; i++) {
      assert(s[n - 1 - i] == '0' || s[n - 1 - i] == '1');
      a[i / w] |= (unsigned long long)(s[n - 1 - i] - '0') << (i % w);
    }
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
    unsigned long long* d;
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

  int next(int i) const {
    assert(0 <= i && i < n);
    int j = i / w;
    if (i % w != w - 1) {
      unsigned long long start = a[j];
      start &= -1ULL << (i % w + 1);
      if (start) return j * w + std::countr_zero(start);
    }
    while (++j < int(a.size())) {
      if (a[j]) return j * w + std::countr_zero(a[j]);
    }
    return n;
  }

  int prev(int i) const {
    assert(0 <= i && i < n);
    int j = i / w;
    if (i % w != 0) {
      unsigned long long start = a[j];
      start &= -1ULL >> (w - i % w);
      if (start) return j * w + (w - 1 - std::countl_zero(start));
    }
    while (--j >= 0) {
      if (a[j]) return j * w + (w - 1 - std::countl_zero(a[j]));
    }
    return -1;
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
        if (i) a[i] |= a[i - 1] >> (w - bit_shift);
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
    return lhs.a == rhs.a;
  }
  friend bool operator!=(const bs& lhs, const bs& rhs) {
    return lhs.a != rhs.a;
  }

  friend std::istream& operator>>(std::istream& is, bs& x) {
    std::string t;
    is >> t;
    x = bs(t);
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, const bs& x) {
    for (int i = x.n - 1; i >= 0; i--) os << x[i];
    return os;
  }

 private:
  static constexpr int w = 64;
  int n;
  std::vector<unsigned long long> a;

  static unsigned long long mask(int pos) { return 1ULL << pos; }
};

}  // namespace cp