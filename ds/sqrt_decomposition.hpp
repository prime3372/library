#pragma once

#include <cassert>
#include <vector>

#include "util/math_utility.hpp"

namespace cp {

template <class block> class sqrt_decomposition {
 public:
  sqrt_decomposition() : n(0), block_size(0), block_num(0) {}
  explicit sqrt_decomposition(int _n, int b)
      : n(_n), block_size(b), block_num((_n + b - 1) / b) {}

  block& get_block(int i) {
    assert(0 <= i && i < block_num);
    return d[i];
  }

  template <class T> T fold_left(int l, int r, T init) {
    assert(0 <= l && l <= r && r <= n);
    int lblock = l / block_size;
    int rblock = r / block_size;
    T ans = init;
    if (lblock == rblock && rblock < block_num) {
      ans = d[lblock].query_part(l % block_size, r % block_size, ans);
    } else {
      ans = d[lblock].query_part(l % block_size, block_size, ans);
      for (int i = lblock + 1; i <= rblock - 1; i++) ans = d[i].query_all(ans);
      if (rblock < block_num)
        ans = d[rblock].query_part(0, r % block_size, ans);
    }
    return ans;
  }

  template <class T> T fold_right(int l, int r, T init) {
    assert(0 <= l && l <= r && r <= n);
    int lblock = l / block_size;
    int rblock = r / block_size;
    T ans = init;
    if (lblock == rblock && rblock < block_num) {
      ans = d[lblock].query_part(l % block_size, r % block_size, ans);
    } else {
      if (rblock < block_num)
        ans = d[rblock].query_part(0, r % block_size, ans);
      for (int i = rblock - 1; i >= lblock + 1; i--) ans = d[i].query_all(ans);
      ans = d[lblock].query_part(l % block_size, block_size, ans);
    }
    return ans;
  }

 private:
  int n, block_size, block_num;
  vector<block> d;
};

}  // namespace cp