#pragma once

#include <algorithm>
#include <cassert>
#include <vector>
#include "../algebra/monoid.hpp"

template <monoid M> struct disjoint_sparse_table {
  using S = typename M::S;

public:
  disjoint_sparse_table() {}
  explicit disjoint_sparse_table(const std::vector<S>& _a) : a(_a) {
    n = int(a.size());
    log = 0;
    while ((1 << log) < n) log++;

    table.resize(log);
    for (int k = 0; k < log; k++) {
      table[k] = a;
      int w = 1 << k;
      for (int l = 0; l < n; l += 2 * w) {
        int r = std::min(l + 2 * w, n), m = std::min(l + w, n);
        for (int i = m - 2; i >= l; i--) {
          table[k][i] = M::op(table[k][i], table[k][i + 1]);
        }
        for (int i = m + 1; i < r; i++) {
          table[k][i] = M::op(table[k][i - 1], table[k][i]);
        }
      }
    }

    logs.resize(1 << log);
    for (int k = 0; k < log; k++) {
      for (int i = 1 << k; i < 1 << (k + 1); i++) {
        logs[i] = k;
      }
    }
  }

  S operator[](int i) {
    assert(0 <= i && i < n);
    return a[i];
  }

  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    if (r - l == 1) return a[l];
    int k = logs[l ^ (r - 1)];
    return M::op(table[k][l], table[k][r - 1]);
  }

private:
  int n, log;
  std::vector<S> a;
  std::vector<std::vector<S>> table;
  std::vector<int> logs;
};
