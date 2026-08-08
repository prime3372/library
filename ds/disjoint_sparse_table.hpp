#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "util/io_utility.hpp"

namespace cp {

template <class M> struct disjoint_sparse_table {
public:
  using S = typename M::S;

  disjoint_sparse_table() : n(0), log(0) {}
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
      for (int i = 1 << k; i < (1 << (k + 1)); i++) {
        logs[i] = k;
      }
    }
  }

  S operator[](int i) const {
    assert(0 <= i && i < n);
    return a[i];
  }

  S prod(int l, int r) const {
    assert(0 <= l && l <= r && r <= n);
    if (r - l == 1) return a[l];
    int k = logs[l ^ (r - 1)];
    return M::op(table[k][l], table[k][r - 1]);
  }

  int size() const { return n; }

  // for debugging
  friend std::ostream& operator<<(std::ostream& os,
                                  const disjoint_sparse_table& dst) {
    for (int i = 0; i < dst.n; i++) {
      os << dst[i];
      if (i != dst.n - 1) {
        os << internal::delimiter_v<S>;
      }
    }
    return os;
  }

private:
  int n, log;
  std::vector<S> a;
  std::vector<std::vector<S>> table;
  std::vector<int> logs;
};

namespace internal {

template <class M> struct delimiter<disjoint_sparse_table<M>> {
  static constexpr char value[] = "\n";
};

} // namespace internal

} // namespace cp