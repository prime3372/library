#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

#include "ds/bit_vector.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <int bit_size> class wavelet_matrix {
  static_assert(0 <= bit_size && bit_size <= 64);
  using ull = unsigned long long;

 public:
  wavelet_matrix() : wavelet_matrix(0) {}
  explicit wavelet_matrix(int _n) : n(_n), a(_n) {}

  void set(int i, ull x) {
    assert(0 <= i && i < n);
    a[i] = x;
  }

  void init() {
    data.assign(bit_size, bit_vector(n));
    std::vector<ull> cur = a, nxt(n);
    for (int h = bit_size - 1; h >= 0; h--) {
      for (int i = 0; i < n; i++) {
        if ((cur[i] >> h) & 1) data[h].set(i);
      }
      data[h].init();
      std::array itr = {nxt.begin(), nxt.begin() + data[h].rank0(n)};
      for (int i = 0; i < n; i++) *(itr[data[h][i]]++) = cur[i];
      std::swap(cur, nxt);
    }
    initialized = true;
  }

  const bit_vector& operator[](int h) const {
    assert(initialized);
    assert(0 <= h && h < bit_size);
    return data[h];
  }

  int next0(int h, int i) const {
    assert(initialized);
    assert(0 <= h && h < bit_size);
    assert(0 <= i && i <= n);
    return data[h].rank0(i);
  }
  int next1(int h, int i) const {
    assert(initialized);
    assert(0 <= h && h < bit_size);
    assert(0 <= i && i <= n);
    return data[h].rank0(n) + data[h].rank1(i);
  }
  int next(int h, int i) const {
    assert(initialized);
    assert(0 <= h && h < bit_size);
    assert(0 <= i && i < n);
    return data[h][i] ? next1(h, i) : next0(h, i);
  }

 private:
  int n;
  std::vector<ull> a;
  std::vector<bit_vector> data;
  bool initialized = false;
};

}  // namespace cp