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
    // Direct the edges such that deg[i] <= deg[to[i]] holds.
    if (1LL * deg[u] * n + u > 1LL * deg[v] * n + v) std::swap(u, v);
    to[u].push_back(v);
  }

  std::vector<int> mark(n, -1);
  std::vector<std::array<int, 3>> res;
  for (int u = 0; u < n; u++) {
    for (int v : to[u]) mark[v] = u;
    for (int v : to[u]) {
      for (int w : to[v]) {
        // Let m be the total number of edges, and define a vertex with a degree
        // of at least sqrt(m) as a heavy vertex.
        // [1] If v is not a heavy vertex, the total number of w is obviously at
        //     most sqrt(m).
        // [2] If v is a heavy vertex, w is also a heavy vertex, based on how
        //     the edges is directed. Since the sum of the degrees of w is at
        //     most 2*m (by the Handshaking Lemma), the total number of w is at
        //     most 2*sqrt(m).
        // Therefore, this for-loop executes only O(sqrt(m)) times.
        if (mark[w] == u) res.push_back({u, v, w});
      }
    }
  }
  return res;
}

}  // namespace cp