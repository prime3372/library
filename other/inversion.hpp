#pragma once

#include <utility>
#include <vector>

#include "ds/fenwick-tree.hpp"
#include "util/algo-utility.hpp"

namespace cp {

template <class T> long long inversion(std::vector<T> a) {
  int n = int(a.size());
  long long ans = 0;
  FenwickTree<T> fw(n);
  auto b = compress(std::move(a));
  for (int i = 0; i < n; i++) {
    ans += fw.sum(b[i] + 1, n);
    fw.add(b[i], 1);
  }
  return ans;
}

}  // namespace cp