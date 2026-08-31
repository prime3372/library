#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

#include "ds/bit_vector.hpp"
#include "ds/coordinate_compression.hpp"
#include "util/type_traits.hpp"

namespace cp {

template <class data> class rectangle_query {
 public:
  rectangle_query() {}

  template <class T>
  void build(const std::vector<long long>& x, const std::vector<long long>& y,
             const std::vector<T>& w) {
    n = int(x.size());
    assert(int(y.size()) == n && int(w.size()) == n);
    if (n == 0) return;

    for (int i = 0; i < n; i++) cc.add({x[i], i});    
    cc.build();
    coordinate_compression cc_y(y);
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
      a[i] = y[cc({x[i], i})];
    }

    max_y = *std::max_element(y.begin(), y.end());
    log = max_y ? std::bit_width(max_y) : 1;

    bv.assign(log, bit_vector(n));
    f(log, z);
    std::vector<ull> cur_y = y, cur_z = z, nxt_y(n), nxt_z(n);
    for (int h = log - 1; h >= 0; h--) {
      for (int i = 0; i < n; i++) {
        if ((cur_y[i] >> h) & 1) bv[h].set(i);
      }
      bv[h].build();
      std::array itr_y = {nxt_y.begin(), nxt_y.begin() + bv[h].zeros()};
      std::array itr_z = {nxt_z.begin(), nxt_z.begin() + bv[h].zeros()};
      for (int i = 0; i < n; i++) {
        *(itr_y[bv[h][i]]++) = cur_y[i];
        *(itr_z[bv[h][i]]++) = cur_z[i];
      }
      std::swap(cur_y, nxt_y);
      std::swap(cur_z, nxt_z);
      f(h, cur_z);
    }
    initialized = true;
  }

  int query(int l, ull d, int r, ull u) const {
    assert(initialized);
    assert(0 <= l && l <= r && r <= size);
    int ans = 0;
    query(l, d, r, u, [&](int, int a, int b) { ans += b - a; });
    return ans;
  }

  template <class F> void query(int l, ull d, int r, ull u, F f) const {
    assert(initialized);
    assert(0 <= l && l <= r && r <= size);
    rectangle_query(log, l, r, 0, -1ULL, d, u, f);
  }

 private:
  int size, log;
  bool initialized = false;
  std::vector<int> a;
  std::vector<long long> x, y;
  coordinate_compression<std::pair<long long, int>> cc;
  std::vector<bit_vector> bv;
  std::vector<data> d;

  template <class F>
  void query(int h, int l0, int r0, ull d0, ull u0, ull d, ull u, F f) const {
    if (u0 < d || u <= d0) return;
    if (d <= d0 && u0 < u) {
      f(d[h], l0, r0);
      return;
    }
    int l1 = bv[h].rank0(l0);
    int r1 = bv[h].rank0(r0);
    ull d1 = d0;
    ull u1 = u0 - (1ULL << (h - 1));
    query(h - 1, l1, r1, d1, u1, d, u, f);
    int l2 = bv[h].rank0(l0);
    int r2 = bv[h].zeros() + r0 - r1;
    ull d2 = d0 + (1ULL << (h - 1));
    ull u2 = u0;
    query(h - 1, l2, r2, d2, u2, d, u, f);
  }
};

}  // namespace cp