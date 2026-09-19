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
  using bs = std::bitset<bit_size>;

 public:
  wavelet_matrix() : wavelet_matrix(0) {}
  explicit wavelet_matrix(int _n) : n(_n), a(_n) {}

  void set(int i, const bs& x) {
    assert(0 <= i && i < n);
    a[i] = x;
  }

  void build() {
    data.assign(bit_size, bit_vector(n));
    std::vector<bs> cur = a, nxt(n);
    for (int h = bit_size - 1; h >= 0; h--) {
      for (int i = 0; i < n; i++) {
        if (cur[i][h]) data[h].set(i);
      }
      data[h].build();
      std::array itr = {nxt.begin(), nxt.begin() + data[h].rank0(n)};
      for (int i = 0; i < n; i++) *(itr[data[h][i]]++) = cur[i];
      std::swap(cur, nxt);
    }
  }

  const bit_vector& operator[](int h) const {
    assert(0 <= h && h < bit_size);
    return data[h];
  }

  int next0(int h, int i) const {
    assert(0 <= h && h < bit_size);
    assert(0 <= i && i <= n);
    return data[h].rank0(i);
  }
  int next1(int h, int i) const {
    assert(0 <= h && h < bit_size);
    assert(0 <= i && i <= n);
    return data[h].rank0(n) + data[h].rank1(i);
  }
  int next(int h, int i) const {
    assert(0 <= h && h < bit_size);
    assert(0 <= i && i < n);
    return data[h][i] ? next1(h, i) : next0(h, i);
  }

 private:
  int n;
  std::vector<bs> a;
  std::vector<bit_vector> data;
};

}  // namespace cp