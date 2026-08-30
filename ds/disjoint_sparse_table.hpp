#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <iostream>
#include <vector>

namespace cp {

template <class S, auto op, auto e> class disjoint_sparse_table {
 public:
  disjoint_sparse_table() : n(0), log(0) {}
  explicit disjoint_sparse_table(const std::vector<S>& _a) { build(_a); }

  disjoint_sparse_table& build(const std::vector<S>& _a) {
    n = int(_a.size());
    log = std::countr_zero(std::bit_ceil((unsigned int)(n)));
    a = _a;

    table.resize(log);
    for (int k = 0; k < log; k++) {
      table[k] = a;
      int w = 1 << k;
      for (int l = 0; l < n; l += 2 * w) {
        int r = std::min(l + 2 * w, n), m = std::min(l + w, n);
        for (int i = m - 2; i >= l; i--) {
          table[k][i] = op(table[k][i], table[k][i + 1]);
        }
        for (int i = m + 1; i < r; i++) {
          table[k][i] = op(table[k][i - 1], table[k][i]);
        }
      }
    }

    log_table.resize(1 << log);
    for (int k = 0; k < log; k++) {
      for (int i = 1 << k; i < (1 << (k + 1)); i++) {
        log_table[i] = k;
      }
    }

    return *this;
  }

  S operator[](int i) const {
    assert(0 <= i && i < n);
    return a[i];
  }

  S prod(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    if (l == r) return e();
    if (l + 1 == r) return a[l];
    int k = log_table[l ^ (r - 1)];
    return op(table[k][l], table[k][r - 1]);
  }

  int size() const { return n; }

 private:
  int n, log;
  std::vector<S> a;
  std::vector<std::vector<S>> table;
  std::vector<int> log_table;
};

}  // namespace cp