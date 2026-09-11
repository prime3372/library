#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

#include "util/type_traits.hpp"

namespace cp {

template <class T> requires(internal::is_unsigned_int_v<T>)
class wavelet_matrix {
 public:
  class bit_vector {
   public:
    bit_vector() {}
    explicit bit_vector(int _n) : n(_n), block(n / 64 + 1), count(n / 64 + 1) {}

    void set(int i) {
      assert(0 <= i && i < n);
      block[i / 64] |= 1LL << (i % 64);
    }

    void build() {
      for (int i = 0; i < int(block.size()) - 1; i++) {
        count[i + 1] = count[i] + std::popcount(block[i]);
      }
    }

    bool operator[](int i) const {
      assert(0 <= i && i < n);
      return (block[i / 64] & mask(i % 64)) != 0;
    }

    int rank0(int i) const {
      assert(0 <= i && i <= n);
      return i - rank1(i);
    }
    int rank1(int i) const {
      assert(0 <= i && i <= n);
      return count[i / 64] + std::popcount(block[i / 64] & (mask(i % 64) - 1));
    }

    int next0(int i) const { return rank0(i); }
    int next1(int i) const { return rank0(n) + rank1(i); }
    int next(int i) const { return (*this)[i] ? next1(i) : next0(i); }

   private:
    int n;
    std::vector<unsigned long long> block;
    std::vector<int> count;

    static unsigned long long mask(int pos) { return 1ULL << pos; }
  };

  static constexpr int digits() { return w; }

  wavelet_matrix() : wavelet_matrix(0) {}
  explicit wavelet_matrix(int _n) : n(_n), a(_n) {}

  void set(int i, T x) {
    assert(0 <= i && i < n);
    a[i] = x;
  }

  wavelet_matrix build() {
    data.assign(w, bit_vector(n));
    std::vector<T> cur = a, nxt(n);
    for (int h = w - 1; h >= 0; h--) {
      for (int i = 0; i < n; i++) {
        if ((cur[i] >> h) & 1) data[h].set(i);
      }
      data[h].build();
      std::array itr = {nxt.begin(), nxt.begin() + data[h].rank0(n)};
      for (int i = 0; i < n; i++) *(itr[data[h][i]]++) = cur[i];
      std::swap(cur, nxt);
    }
    return *this;
  }

  const bit_vector& operator[](int h) const {
    assert(0 <= h && h < w);
    return data[h];
  }

 private:
  static constexpr int w = std::numeric_limits<T>::digits;
  int n;
  std::vector<T> a;
  std::vector<bit_vector> data;
};

}  // namespace cp