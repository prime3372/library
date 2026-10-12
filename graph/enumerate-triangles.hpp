#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <limits>
#include <tuple>
#include <utility>
#include <vector>

namespace cp {

// Enumerate the triples of vertices that form a cycle.
std::vector<std::array<int, 3>> enumerate_triangles(
    int n, std::vector<std::pair<int, int>> edges) {
  assert(0 <= n);
  for (auto& [u, v] : edges) {
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    if (u > v) std::swap(u, v);
  }
  std::sort(edges.begin(), edges.end());
  edges.erase(std::unique(edges.begin(), edges.end()), edges.end());
  edges.erase(
      std::remove_if(edges.begin(), edges.end(),
                     [&](const auto& e) { return e.first == e.second; }),
      edges.end());

  std::vector<int> deg(n);
  for (auto [u, v] : edges) deg[u]++, deg[v]++;
  std::vector<std::vector<int>> to(n);
  for (auto [u, v] : edges) {
    // Direct the edges such that deg[i] <= deg[to[i][j]] holds.
    if (1LL * deg[u] * n + u > 1LL * deg[v] * n + v) std::swap(u, v);
    to[u].push_back(v);
  }

  std::vector<int> mark(n, -1);
  std::vector<std::array<int, 3>> res;
  for (int u = 0; u < n; u++) {
    for (int v : to[u]) mark[v] = u;
    for (int v : to[u]) {
      for (int w : to[v]) {
        // For all w in to[v], the condition deg[v] <= deg[w] holds. By the
        // handshaking lemma, the sum of deg[w] does not exceed 2m, so
        // deg[v] does not exceed 2*sqrt(m). Therefore, the number of times this
        // for-loop executes is limited to O(sqrt(m)).
        if (mark[w] == u) res.push_back({u, v, w});
      }
    }
  }
  return res;
}

}  // namespace cp