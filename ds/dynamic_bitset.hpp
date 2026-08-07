#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace cp {

struct dynamic_bitset {
public:
  using bs = dynamic_bitset;

  dynamic_bitset() : n(0) {}
  explicit dynamic_bitset(int _n) : n(_n), a((_n + 63) / 64, 0) {}
  explicit dynamic_bitset(int _n, bool b) : n(_n), a((_n + 63) / 64, b ? -1 : 0) {
    if (b && n % 64) a.back() &= mask(n % 64) - 1;
  }
  explicit dynamic_bitset(const std::string& s) : n(int(s.size())), a((int(s.size()) + 63) / 64) {
    for (int i = 0; i < n; i++) {
      assert(s[n - 1 - i] == '0' || s[n - 1 - i] == '1');
      a[i / 64] |= (unsigned long long)(s[n - 1 - i] - '0') << (i % 64);
    }
  }

  struct ref {
  public:
    operator bool() const { return (*d & mask(pos)) != 0; }
    ref& flip() {
      *d ^= mask(pos);
      return *this;
    }
    ref& operator=(bool x) {
      if (x) *d |= mask(pos);
      else *d &= ~mask(pos);
      return *this;
    }
    ref& operator=(const ref& other) { return *this = bool(other); }
    ref(bs& b, int i) {
      d = b.a.data() + i / 64;
      pos = i % 64;
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
    return (a[i / 64] & mask(i % 64)) != 0;
  }

  bs& flip() {
    if (n == 0) return *this;
    for (int i = 0; i < int(a.size()); i++) {
      a[i] = ~a[i];
    }
    if (n % 64) a.back() &= mask(n % 64) - 1;
    return *this;
  }
  bs operator~() const {
    return bs(*this).flip();
  }

  int count() const {
    int res = 0;
    for (int i = 0; i < int(a.size()); i++) {
      res += std::popcount(a[i]);
    }
    return res;
  }

  int next(int i) const {
    assert(0 <= i && i < n);
    int j = i / 64;
    if (i % 64 != 63) {
      unsigned long long start = a[j];
      start &= (unsigned long long)(-1) << (i % 64 + 1);
      if (start) return 64 * j + std::countr_zero(start);
    }
    while (++j < int(a.size())) {
      if (a[j]) return 64 * j + std::countr_zero(a[j]);
    }
    return n;
  }

  int prev(int i) const {
    assert(0 <= i && i < n);
    int j = i / 64;
    if (i % 64 != 0) {
      unsigned long long start = a[j];
      start &= (unsigned long long)(-1) >> (64 - i % 64);
      if (start) return 64 * j + 63 - std::countl_zero(start);
    }
    while (--j >= 0) {
      if (a[j]) return 64 * j + 63 - std::countl_zero(a[j]);
    }
    return -1;
  }

  int size() const { return n; }

  bs& operator^=(const bs& rhs) {
    assert(n == rhs.n);
    for (int i = 0; i < int(a.size()); i++) a[i] ^= rhs.a[i];
    return *this;
  }
  bs& operator|=(const bs& rhs) {
    assert(n == rhs.n);
    for (int i = 0; i < int(a.size()); i++) a[i] |= rhs.a[i];
    return *this;
  }
  bs& operator&=(const bs& rhs) {
    assert(n == rhs.n);
    for (int i = 0; i < int(a.size()); i++) a[i] &= rhs.a[i];
    return *this;
  }

  bs& operator<<=(int shift) {
    assert(0 <= shift);
    if (n == 0) return *this;
    if (shift >= n) {
      std::fill(a.begin(), a.end(), 0);
      return *this;
    }

    int block_shift = shift / 64;    
    if (block_shift > 0) {
      for (int i = int(a.size()) - 1; i >= block_shift; i--) {
        a[i] = a[i - block_shift]; 
      }
      std::fill(a.begin(), a.begin() + block_shift, 0);
    }

    int bit_shift = shift % 64;
    if (bit_shift > 0) {
      for (int i = int(a.size()) - 1; i > block_shift; i--) {
        a[i] <<= bit_shift;
        if (i) a[i] |= a[i - 1] >> (64 - bit_shift);
      }
      a[block_shift] <<= bit_shift;
    }

    if (n % 64) a.back() &= mask(n % 64) - 1;
    return *this;
  }

  bs& operator>>=(int shift) {
    assert(0 <= shift);
    if (n == 0) return *this;
    if (shift >= n) {
      std::fill(a.begin(), a.end(), 0);
      return *this;
    }

    int block_shift = shift / 64;
    if (block_shift > 0) {
      for (int i = 0; i < int(a.size()) - block_shift; i++) {
        a[i] = a[i + block_shift];
      }
      std::fill(a.end() - block_shift, a.end(), 0);
    }

    int bit_shift = shift % 64;
    if (bit_shift > 0) {
      for (int i = 0; i < int(a.size()) - block_shift - 1; i++) {
        a[i] >>= bit_shift;
        a[i] |= a[i + 1] << (64 - bit_shift);
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
  int n;
  std::vector<unsigned long long> a;

  static unsigned long long mask(int pos) { return 1ULL << pos; }
};

} // namespace cp