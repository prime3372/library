#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "random_tree.hpp"
#include "rng.hpp"

namespace cp {

template <bool directed = false, bool has_self_loops = false>
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
      if constexpr (has_self_loops) {
        u = mt32() % n;
        v = mt32() % n;
      } else {
        u = mt32() % (n - 1);
        v = mt32() % (n - u - 1) + u + 1;
        if (mt32() % 2) std::swap(u, v);
      }
    } else {
      if constexpr (has_self_loops) {
        u = mt32() % n;
        v = mt32() % (n - u) + u;
      } else {
        u = mt32() % (n - 1);
        v = mt32() % (n - u - 1) + u + 1;
      }
    }
    edges[i] = {u, v};
  }
  
  return edges;
}

int erase_multiple_edges(std::vector<std::pair<int, int>>& edges) {
  std::sort(edges.begin(), edges.end());
  edges.erase(std::unique(edges.begin(), edges.end()), edges.end());
  std::shuffle(edges.begin(), edges.end(), mt32);
  return int(edges.size());
}

} // namespace cp