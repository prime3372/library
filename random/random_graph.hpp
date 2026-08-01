#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "random/rng.hpp"

namespace cp {

template <bool directed = false, bool has_self_loops = false>
std::vector<std::pair<int, int>> random_graph(int n, int m) {
  assert(0 <= n && 0 <= m);

  if (n == 0 || (!has_self_loops && n == 1)) {
    assert(m == 0);
    return {};
  }

  std::vector<std::pair<int, int>> edges(m);
  for (int i = 0; i < m; i++) {
    int u, v;
    if constexpr (directed) {
      if constexpr (has_self_loops) {
        u = get_rand(0, n);
        v = get_rand(0, n);
      } else {
        u = get_rand(0, n - 1);
        v = get_rand(u + 1, n);
        if (get_rand(2)) std::swap(u, v);
      }
    } else {
      if constexpr (has_self_loops) {
        u = get_rand(0, n);
        v = get_rand(u, n);
      } else {
        u = get_rand(0, n - 1);
        v = get_rand(u, n);
      }
    }
    edges[i] = {u, v};
  }
  
  return edges;
}

int remove_multiple_edges(std::vector<std::pair<int, int>>& edges) {
  std::sort(edges.begin(), edges.end());
  edges.erase(std::unique(edges.begin(), edges.end()), edges.end());
  std::shuffle(edges.begin(), edges.end(), mt32);
  return int(edges.size());
}

} // namespace cp