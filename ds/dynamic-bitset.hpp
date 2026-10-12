#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

namespace cp {

struct DynamicBitset {
  using ull = unsigned long long;

 public:
  DynamicBitset() : n(0) {}
  explicit DynamicBitset(int _n) : n(_n), a((_n + w - 1) / w) {}

  class ref {
   public:
    operator bool() const { return (*d & mask(pos)) != 0; }
    ref& flip() {
      *d ^= mask(pos);
      return *this;
    }
    ref& operator=(bool x) {
      if (x)
        *d |= mask(pos);
      else
        *d &= ~mask(pos);
      return *this;
    }
    ref& operator=(const ref& other) { return *this = bool(other); }

   private:
    friend DynamicBitset;
    ull* d;
    int pos;
    ref(DynamicBitset& b, int i) {
      d = b.a.data() + i / w;
      pos = i % w;
    }
  };

  ref operator[](int i) {
    assert(0 <= i && i < n);
    return ref(*this, i);
  }
  bool operator[](int i) const {
    assert(0 <= i && i < n);
    return (a[i / w] & mask(i % w)) != 0;
  }

  DynamicBitset& flip() {
    if (n == 0) return *this;
    for (int i = 0; i < int(a.size()); i++) a[i] = ~a[i];
    if (n % w) a.back() &= mask(n % w) - 1;
    return *this;
  }
  DynamicBitset operator~() const { return DynamicBitset(*this).flip(); }

  int count() const {
    int res = 0;
    for (int i = 0; i < int(a.size()); i++) res += std::popcount(a[i]);
    return res;
  }

  int size() const { return n; }

  DynamicBitset& operator^=(const DynamicBitset& rhs) {
    assert(n == rhs.n);
    for (int i = 0; i < int(a.size()); i++) a[i] ^= rhs.a[i];
    return *this;
  }
  DynamicBitset& operator|=(const DynamicBitset& rhs) {
    assert(n == rhs.n);
    for (int i = 0; i < int(a.size()); i++) a[i] |= rhs.a[i];
    return *this;
  }
  DynamicBitset& operator&=(const DynamicBitset& rhs) {
    assert(n == rhs.n);
    for (int i = 0; i < int(a.size()); i++) a[i] &= rhs.a[i];
    return *this;
  }

  DynamicBitset& operator<<=(int shift) {
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

  DynamicBitset& operator>>=(int shift) {
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

  friend DynamicBitset operator^(const DynamicBitset& lhs,
                                 const DynamicBitset& rhs) {
    return DynamicBitset(lhs) ^= rhs;
  }
  friend DynamicBitset operator|(const DynamicBitset& lhs,
                                 const DynamicBitset& rhs) {
    return DynamicBitset(lhs) |= rhs;
  }
  friend DynamicBitset operator&(const DynamicBitset& lhs,
                                 const DynamicBitset& rhs) {
    return DynamicBitset(lhs) &= rhs;
  }
  friend DynamicBitset operator<<(const DynamicBitset& lhs, int shift) {
    return DynamicBitset(lhs) <<= shift;
  }
  friend DynamicBitset operator>>(const DynamicBitset& lhs, int shift) {
    return DynamicBitset(lhs) >>= shift;
  }

  friend bool operator==(const DynamicBitset& lhs, const DynamicBitset& rhs) {
    assert(lhs.n == rhs.n);
    return lhs.a == rhs.a;
  }
  friend bool operator!=(const DynamicBitset& lhs, const DynamicBitset& rhs) {
    return !(lhs == rhs);
  }

 private:
  static constexpr int w = 64;
  int n;
  std::vector<ull> a;

  static ull mask(int pos) { return 1ULL << pos; }
};

}  // namespace cp