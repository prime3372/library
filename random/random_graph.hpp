#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

#include "random_tree.hpp"
#include "rng.hpp"

namespace cp {

template <bool directed = false, bool has_self_loops = false, bool has_multiple_edges = false>
std::vector<std::pair<int, int>> random_graph(int n, int m) {
  assert(0 <= n && 0 <= m);
  std::vector<std::pair<int, int>> edges(m);

  if (n == 0 || !has_self_loops && n == 1) {
    assert(m == 0);
    return {};
  }

  if constexpr (has_multiple_edges) {
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

  long long max_m = 1LL * n * (has_self_loops ? n : (n - 1));
  if constexpr (!directed) max_m /= 2;
  assert((long long)(m) <= max_m);

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

std::vector<std::pair<int, int>> random_connected_graph(int n,
                                                        int m,
                                                        bool directed = false,
                                                        bool has_self_loops = false) {
  assert(n - 1 <= m);
  
}

} // namespace cp