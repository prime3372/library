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
  using ull = unsigned long long;

 public:
  class bit_vector {
   public:
    bit_vector() {}
    explicit bit_vector(int _n) : n(_n), block(n / w + 1), count(n / w + 1) {}

    void set(int i) {
      assert(0 <= i && i < n);
      block[i / w] |= 1LL << (i % w);
    }

    void build() {
      for (int i = 1; i < int(block.size()); i++) {
        count[i] = count[i - 1] + std::popcount(block[i - 1]);
      }
    }

    bool operator[](int i) const {
      assert(0 <= i && i < n);
      return (block[i / w] & (1ULL << (i % w))) != 0;
    }

    int rank0(int i) const {
      assert(0 <= i && i <= n);
      return i - rank1(i);
    }
    int rank0() const { return rank0(n); }

    int rank1(int i) const {
      assert(0 <= i && i <= n);
      return count[i / w] +
             std::popcount(block[i / w] & ((1ULL << (i % w)) - 1));
    }
    int rank1() const { return rank1(n); }

    int next0(int i) const { return rank0(i); }
    int next1(int i) const { return rank0() + rank1(i); }

   private:
    static constexpr int w = 64;
    int n;
    std::vector<unsigned long long> block;
    std::vector<int> count;
  };

  wavelet_matrix() : wavelet_matrix(0) {}
  explicit wavelet_matrix(int _n) : n(_n), a(_n) {}

  void set(int i, T x) {
    assert(0 <= i && i < n);
    a[i] = x;
  }

  std::vector<bit_vector> data;
  std::vector<std::vector<int>> index;

  wavelet_matrix build() {
    data.assign(w, bit_vector(n));
    std::vector<T> cur = a, nxt(n);
    for (int h = w - 1; h >= 0; h--) {
      for (int i = 0; i < n; i++) {
        if ((cur[i] >> h) & 1) data[h].set(i);
      }
      data[h].build();
      std::array itr = {nxt.begin(), nxt.begin() + data[h].rank0()};
      for (int i = 0; i < n; i++) *(itr[data[h][i]]++) = cur[i];
      std::swap(cur, nxt);
    }

    index.assign(w, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
      int k = i;
      for (int h = w - 1; h >= 0; h--) {
        k = data[h][k] ? data[h].next1(k) : data[h].next0(k);
        index[h][k] = i;
      }
    }
    return *this;
  }

  const bit_vector& operator[](int i) { return data[i]; }

 private:
  int w = std::numeric_limits<T>::digits;
  int n;
  std::vector<T> a;
};

}  // namespace cp