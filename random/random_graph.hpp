#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

#include "ds/hash_set.hpp"
#include "random/base.hpp"
#include "random/random_tree.hpp"

namespace cp {

template <bool directed = false, bool no_self_loops = false,
          bool no_multiple_edges = false, bool connected = false,
          bool one_indexed = true>
std::vector<std::pair<int, int>> random_graph(int n, int m, int s = 0) {
  assert(0 <= n && 0 <= m);
  if (n == 0) {
    assert(m == 0);
    return {};
  } else if (n == 1) {
    if (m == 0) return {};
    assert(!no_self_loops);
  }

  std::vector<std::pair<int, int>> edges;
  edges.reserve(m);

  if (connected) {
    assert(n - 1 <= m);
    if (directed) {
      assert(0 <= s && s < n);
      auto tree = random_rooted_tree<false>(n, s);
      for (int i = 0; i < n; i++) {
        if (i == s) continue;
        edges.emplace_back(tree[i], i);
      }
    } else {
      auto tree = random_tree<false>(n);
      for (auto& e : tree) {
        if (e.first > e.second) std::swap(e.first, e.second);
        edges.emplace_back(e);
      }
    }
  }

  auto next_edge = [&]() {
    int u, v;
    if (directed) {
      if (no_self_loops) {
        u = uniform(0, n - 2);
        v = uniform(u + 1, n - 1);
        if (uniform_bool()) std::swap(u, v);
      } else {
        u = uniform(0, n - 1);
        v = uniform(0, n - 1);
      }
    } else {
      if (no_self_loops) {
        u = uniform(0, n - 2);
        v = uniform(u + 1, n - 1);
      } else {
        u = uniform(0, n - 1);
        v = uniform(u, n - 1);
      }
    }
    return std::make_pair(u, v);
  };

  [&] {
    if (!no_multiple_edges) {
      while (int(edges.size()) < m) {
        edges.emplace_back(next_edge());
      }
      return;
    }

    long long max_m;
    if (directed) {
      max_m = no_self_loops ? 1LL * n * (n - 1) : 1LL * n * n;
    } else {
      max_m = no_self_loops ? 1LL * n * (n - 1) / 2 : n * (n + 1) / 2;
    }
    assert(m <= max_m);

    hash_set<long long> used_edges;
    for (auto [u, v] : edges) used_edges.insert(1LL * u * n + v);

    if (m <= max_m / 2) {
      while (int(edges.size()) < m) {
        auto [u, v] = next_edge();
        if (used_edges.count(1LL * u * n + v)) continue;
        edges.emplace_back(u, v);
        used_edges.insert(1LL * u * n + v);
      }
      return;
    }

    std::vector<std::pair<int, int>> candidates;
    candidates.reserve(max_m - used_edges.size());
    for (int u = 0; u < n; u++) {
      for (int v = directed ? 0 : u; v < n; v++) {
        if (no_self_loops && u == v) continue;
        if (!used_edges.count(1LL * u * n + v)) candidates.emplace_back(u, v);
      }
    }
    std::shuffle(candidates.begin(), candidates.end(), mt32);
    int needed = m - int(edges.size());
    for (int i = 0; i < needed; i++) {
      edges.emplace_back(candidates[i]);
    }
  }();

  if (!directed) {
    for (auto& e : edges) {
      if (uniform_bool()) std::swap(e.first, e.second);
    }
  }
  if (one_indexed) {
    for (auto& e : edges) {
      e.first++;
      e.second++;
    }
  }
  return edges;
}

}  // namespace cp