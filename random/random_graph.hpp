#pragma once

#include <algorithm>
#include <cassert>
#include <numeric>
#include <utility>
#include <vector>

#include "ds/hash_set.hpp"
#include "random/base.hpp"
#include "random/random_tree.hpp"

namespace cp {

template <bool has_self_loops = true, bool has_multiple_edges = true,
          bool connected = false>
std::vector<std::pair<int, int>> random_undirected_graph(int n, int m) {
  assert(0 <= n && 0 <= m);
  if (n == 0) {
    assert(m == 0);
    return {};
  }

  std::vector<std::pair<int, int>> edges;
  edges.reserve(m);

  if (connected) {
    assert(n - 1 <= m);
    auto tree = random_tree(n);
    for (auto& e : tree) {
      if (e.first > e.second) std::swap(e.first, e.second);
      edges.emplace_back(e);
    }
  }

  if (has_multiple_edges) {
    while (int(edges.size()) < m) {
      int u, v;
      if (has_self_loops) {
        u = uniform(0, n - 1);
        v = uniform(u, n - 1);
      } else {
        u = uniform(0, n - 2);
        v = uniform(u + 1, n - 1);
      }
      if (uniform_bool()) std::swap(u, v);
      edges.emplace_back(u, v);
    }
    return edges;
  }

  long long max_m =
      has_self_loops ? 1LL * n * (n + 1) / 2 : 1LL * n * (n - 1) / 2;
  assert(m <= max_m);

  hash_set<long long> used_edges;
  for (auto [u, v] : edges) { used_edges.insert(1LL * u * n + v); }

  if (m > max_m / 2) {
    std::vector<std::pair<int, int>> candidates;
    candidates.reserve(max_m - used_edges.size());
    for (int u = 0; u < n; u++) {
      for (int v = u; v < n; v++) {
        if (!has_self_loops && u == v) continue;
        if (!used_edges.count(1LL * u * n + v)) {
          candidates.emplace_back(u, v);
        }
      }
    }
    std::shuffle(candidates.begin(), candidates.end(), mt32);
    int needed = m - int(edges.size());
    for (int i = 0; i < needed; i++) edges.emplace_back(candidates[i]);
  } else {
    while (int(edges.size()) < m) {
      int u, v;
      if (has_self_loops) {
        u = uniform(0, n - 1);
        v = uniform(u, n - 1);
      } else {
        u = uniform(0, n - 2);
        v = uniform(u + 1, n - 1);
      }
      if (used_edges.count(1LL * u * n + v)) continue;
      edges.emplace_back(u, v);
      used_edges.insert(1LL * u * n + v);
    }
  }

  for (auto& e : edges) {
    if (uniform_bool()) std::swap(e.first, e.second);
  }
  return edges;
}

// @note If connected is true, all the vertices are reachable from vertex s.
template <bool has_self_loops = true, bool has_multiple_edges = true,
          bool connected = false>
std::vector<std::pair<int, int>> random_directed_graph(int n, int m,
                                                       int s = 0) {
  assert(0 <= n && 0 <= m);
  if (n == 0) {
    assert(m == 0);
    return {};
  }

  std::vector<std::pair<int, int>> edges;
  edges.reserve(m);

  if (connected) {
    assert(0 <= s && s < n);
    assert(n - 1 <= m);
    auto par = random_rooted_tree(n, s);
    for (int i = 0; i < n; i++) {
      if (i == s) continue;
      edges.emplace_back(par[i], i);
    }
  }

  if (has_multiple_edges) {
    assert(n - 1 <= m);
    while (int(edges.size()) < m) {
      int u, v;
      if (has_self_loops) {
        u = uniform(0, n - 1);
        v = uniform(0, n - 1);
      } else {
        u = uniform(0, n - 2);
        v = uniform(u + 1, n - 1);
        if (uniform_bool()) std::swap(u, v);
      }
      edges.emplace_back(u, v);
    }
    return edges;
  }

  long long max_m = has_self_loops ? 1LL * n * n : 1LL * n * (n - 1);
  assert(m <= max_m);

  hash_set<long long> used_edges;
  for (auto [u, v] : edges) { used_edges.insert(1LL * u * n + v); }

  if (m > max_m / 2) {
    std::vector<std::pair<int, int>> candidates;
    candidates.reserve(max_m - used_edges.size());
    for (int u = 0; u < n; u++) {
      for (int v = 0; v < n; v++) {
        if (!has_self_loops && u == v) continue;
        if (!used_edges.count(1LL * u * n + v)) {
          candidates.emplace_back(u, v);
        }
      }
    }
    std::shuffle(candidates.begin(), candidates.end(), mt32);
    int needed = m - int(edges.size());
    for (int i = 0; i < needed; ++i) { edges.emplace_back(candidates[i]); }
  } else {
    while (int(edges.size()) < m) {
      int u, v;
      if (has_self_loops) {
        u = uniform(0, n - 1);
        v = uniform(0, n - 1);
      } else {
        u = uniform(0, n - 2);
        v = uniform(u + 1, n - 1);
        if (uniform_bool()) std::swap(u, v);
      }
      if (used_edges.count(1LL * u * n + v)) continue;
      edges.emplace_back(u, v);
      used_edges.insert(1LL * u * n + v);
    }
  }

  return edges;
}

}  // namespace cp