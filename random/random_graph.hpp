#pragma once

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
#include "random_tree.hpp"
#include "rng.hpp"

template <class T>
std::vector<std::pair<T, T>> random_graph(T n,
                                          int m,
                                          bool directed = false,
                                          bool has_self_loops = false,
                                          bool has_multiple_edges = false) {
  assert(0 <= n && 0 <= m);
  std::vector<std::pair<T, T>> edges(m);

  if (n == 0 || !has_self_loops && n == 1) {
    assert(m == 0);
    return {};
  }

  if (has_multiple_edges) {
    for (int i = 0; i < m; i++) {
      T u, v;
      if (has_self_loops) {
        u = mt64() % n;
        v = mt64() % n;
      } else {
        u = mt64() % (n - 1);
        v = mt64() % (n - u - 1) + u + 1;
      }
      edges[i] = {u, v};
    }
    return edges;
  }

  long long max_m = 1LL * n * (has_self_loops ? n : (n - 1));
  if (!directed) max_m /= 2;
  assert((long long)(m) <= max_m);

  for (int i = 0; i < m; i++) {
    auto choice = random_choice(n, )
  }

  return edges;
}

std::vector<std::pair<int, int>> random_connected_graph(int n,
                                                        int m,
                                                        bool directed = false,
                                                        bool has_self_loops = false) {
  assert(n - 1 <= m);

}