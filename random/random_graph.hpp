#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "random_tree.hpp"
#include "rng.hpp"

namespace cp {

template <bool directed = false>
std::vector<std::pair<int, int>> random_graph(int n, int m) {
  assert(0 <= n && 0 <= m);

  if (n == 0 || !has_self_loops && n == 1) {
    assert(m == 0);
    return {};
  }

  std::vector<std::pair<int, int>> edges(m);
  for (int i = 0; i < m; i++) {
    int u, v;
    if constexpr (directed) {
      u = mt32() % n;
      v = mt32() % n;
    } else {
      u = mt32() % n;
      v = mt32() % (n - u) + u;
    }
    edges[i] = {u, v};
  }
  return edges;
}


} // namespace cp