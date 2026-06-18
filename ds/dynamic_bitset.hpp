#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

struct dynamic_bitset {
public:
  struct ref {
    friend struct dynamic_bitset;
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
    ref& operator=(const ref& other) { return *this = (bool)other; }
  private:
    unsigned long long* d;
    size_t pos;
    ref(dynamic_bitset& b, size_t i) {
      d = b.a.data() + i / 64;
      pos = i % 64;
    }
  };

  dynamic_bitset() : n(0) {}
  explicit dynamic_bitset(size_t _n) : n(_n), a((_n + 63) / 64, 0) {}
  explicit dynamic_bitset(size_t _n, bool b) : n(_n), a((_n + 63) / 64, b ? (unsigned long long)(-1) : 0) {
    if (b && n % 64) a.back() &= mask(n % 64) - 1;
  }
  explicit dynamic_bitset(const std::string& s) : n(s.size()), a((s.size() + 63) / 64) {
    for (size_t i = 0; i < n; i++) {
      assert(s[n - 1 - i] == '0' || s[n - 1 - i] == '1');
      a[i / 64] |= (unsigned long long)(s[n - 1 - i] - '0') << (i % 64);
    }
  }

  ref operator[](size_t i) {
    assert(i < n);
    return ref(*this, i);
  }
  bool operator[](size_t i) const {
    assert(i < n);
    return (a[i / 64] & mask(i % 64)) != 0;
  }

  dynamic_bitset& flip() { return flip(n); }
  dynamic_bitset& flip(size_t l, size_t r) {
    assert(l <= r && r <= n);
    flip(r);
    flip(l);
    return *this;
  }
  dynamic_bitset& flip(size_t r) {
    assert(r <= n);
    if (r == 0) return *this;
    for (size_t i = 0; i < r / 64; i++) {
      a[i] = ~a[i];
    }
    a[(r - 1) / 64] ^= mask(r % 64) - 1;
    return *this;
  }
  dynamic_bitset operator~() const {
    return dynamic_bitset(*this).flip();
  }

  size_t count() const { return count(n); }
  size_t count(size_t l, size_t r) const {
    assert(l <= r && r <= n);
    return count(r) - count(l);
  }
  size_t count(size_t r) const {
    assert(r <= n);
    if (r == 0) return 0;
    size_t res = 0;
    for (size_t i = 0; i < r / 64; i++) {
      res += std::popcount(a[i]);
    }
    res += std::popcount(a[(r - 1) / 64] & (mask(r % 64) - 1));
    return res;
  }

  size_t find(size_t i) const {
    assert(i <= n);
    if (i == n) return n;
    size_t j = i / 64;
    unsigned long long first = a[j];
    first &= (unsigned long long)(-1) << (i % 64);
    if (first) return j * 64 + std::countr_zero(first);
    while (++j < a.size()) {
      if (a[j]) return j * 64 + std::countr_zero(a[j]);
    }
    return n;
  }

  size_t size() const { return n; }

  dynamic_bitset& operator^=(const dynamic_bitset& rhs) {
    assert(n == rhs.n);
    for (size_t i = 0; i < a.size(); i++) a[i] ^= rhs.a[i];
    return *this;
  }
  dynamic_bitset& operator|=(const dynamic_bitset& rhs) {
    assert(n == rhs.n);
    for (size_t i = 0; i < a.size(); i++) a[i] |= rhs.a[i];
    return *this;
  }
  dynamic_bitset& operator&=(const dynamic_bitset& rhs) {
    assert(n == rhs.n);
    for (size_t i = 0; i < a.size(); i++) a[i] &= rhs.a[i];
    return *this;
  }

  dynamic_bitset& operator<<=(size_t shift) {
    if (n == 0) return *this;
    if (shift >= n) {
      std::fill(a.begin(), a.end(), 0);
      return *this;
    }

    size_t block_shift = shift / 64;    
    if (block_shift > 0) {
      for (size_t i = a.size() - 1; i >= block_shift; i--) {
        a[i] = a[i - block_shift]; 
      }
      std::fill(a.begin(), a.begin() + block_shift, 0);
    }

    size_t bit_shift = shift % 64;
    if (bit_shift > 0) {
      for (size_t i = a.size() - 1; i > block_shift; i--) {
        a[i] <<= bit_shift;
        if (i) a[i] |= a[i - 1] >> (64 - bit_shift);
      }
      a[block_shift] <<= bit_shift;
    }

    if (n % 64) a.back() &= mask(n % 64) - 1;
    return *this;
  }
  dynamic_bitset& operator>>=(size_t shift) {
    if (n == 0) return *this;
    if (shift >= n) {
      std::fill(a.begin(), a.end(), 0);
      return *this;
    }

    size_t block_shift = shift / 64;
    if (block_shift > 0) {
      for (size_t i = 0; i < a.size() - block_shift; i++) {
        a[i] = a[i + block_shift];
      }
      std::fill(a.end() - block_shift, a.end(), 0);
    }

    size_t bit_shift = shift % 64;
    if (bit_shift > 0) {
      for (size_t i = 0; i < a.size() - block_shift - 1; i++) {
        a[i] >>= bit_shift;
        a[i] |= a[i + 1] << (64 - bit_shift);
      }
      a[a.size() - block_shift - 1] >>= bit_shift;
    }

    return *this;
  }

  friend dynamic_bitset operator^(const dynamic_bitset& lhs, const dynamic_bitset& rhs) { return dynamic_bitset(lhs) ^= rhs; }
  friend dynamic_bitset operator|(const dynamic_bitset& lhs, const dynamic_bitset& rhs) { return dynamic_bitset(lhs) |= rhs; }
  friend dynamic_bitset operator&(const dynamic_bitset& lhs, const dynamic_bitset& rhs) { return dynamic_bitset(lhs) &= rhs; }
  friend dynamic_bitset operator<<(const dynamic_bitset& lhs, size_t shift) { return dynamic_bitset(lhs) <<= shift; }
  friend dynamic_bitset operator>>(const dynamic_bitset& lhs, size_t shift) { return dynamic_bitset(lhs) >>= shift; }

  friend std::istream& operator>>(std::istream& is, dynamic_bitset& x) {
    std::string t;
    is >> t;
    x = dynamic_bitset(t); return is;
  }
  friend std::ostream& operator<<(std::ostream& os, const dynamic_bitset& x) {
    for (size_t i = 0; i < x.n; i++) os << x[x.n - 1 - i];
    return os;
  }

private:
  size_t n;
  std::vector<unsigned long long> a;

  static constexpr unsigned long long mask(size_t pos) { return 1ULL << pos; }
};
