#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

#include "ds/hash_set.hpp"
#include "random/engine.hpp"
#include "random/random_tree.hpp"

namespace cp {

struct random_graph_config {
  bool directed = false;
  bool no_self_loops = false;
  bool no_multiple_edges = false;
  bool connected = false;
  bool one_indexed = true;
  int start = -1;
};

std::vector<std::pair<int, int>> random_graph(int n, int m,
                                              random_graph_config config = {}) {
  auto [directed, no_self_loops, no_multiple_edges, connected, one_indexed,
        start] = config;

  assert(0 <= n && 0 <= m);
  if (n == 0) {
    assert(m == 0);
    assert(!directed || !connected);
    return {};
  } else if (n == 1) {
    if (m == 0) return {};
    assert(!no_self_loops);
  }

  if (connected) assert(n - 1 <= m);
  if (!connected || !directed) assert(start == -1);

  long long max_m = directed ? (no_self_loops ? 1LL * n * (n - 1) : 1LL * n * n)
                             : (no_self_loops ? 1LL * n * (n - 1) / 2
                                              : 1LL * n * (n + 1) / 2);

  if (no_multiple_edges) assert(m <= max_m);

  std::vector<std::pair<int, int>> edges;
  edges.reserve(m);

  if (connected) {
    if (directed) {
      assert(0 <= start && start < n);
      auto tree = random_rooted_tree<false>(n, start);
      for (int i = 0; i < n; i++) {
        if (i == start) continue;
        edges.emplace_back(tree[i], i);
      }
    } else {
      auto tree = random_tree<false>(n);
      for (auto [u, v] : tree) {
        if (u > v) std::swap(u, v);
        edges.emplace_back(u, v);
      }
    }
  }

  auto next_edge = [&]() {
    int u = uniform(0, n - 1);
    int v = no_self_loops ? uniform(0, n - 2) : uniform(0, n - 1);
    if (no_self_loops && u <= v) v++;
    if (!directed && u > v) std::swap(u, v);
    return std::make_pair(u, v);
  };

  if (no_multiple_edges) {
    hash_set<long long> used_edges;
    for (auto [u, v] : edges) used_edges.insert(1LL * u * n + v);

    if (m <= max_m / 2) {
      while (int(edges.size()) < m) {
        auto [u, v] = next_edge();
        if (used_edges.insert(1LL * u * n + v)) {
          edges.emplace_back(u, v);
        }
      }
    } else {
      std::vector<std::pair<int, int>> candidates;
      candidates.reserve(max_m - used_edges.size());
      for (int u = 0; u < n; u++) {
        for (int v = directed ? 0 : u; v < n; v++) {
          if (no_self_loops && u == v) continue;
          if (!used_edges.count(1LL * u * n + v)) candidates.emplace_back(u, v);
        }
      }
      shuffle(candidates);
      int needed = m - int(edges.size());
      edges.insert(edges.end(), candidates.begin(),
                   candidates.begin() + needed);
    }
  } else {
    while (int(edges.size()) < m) {
      edges.emplace_back(next_edge());
    }
  }

  for (auto& [u, v] : edges) {
    if (!directed && uniform_bool()) std::swap(u, v);
    if (one_indexed) u++, v++;
  }

  return edges;
}

}  // namespace cp