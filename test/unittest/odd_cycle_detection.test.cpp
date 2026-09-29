#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "graph/odd_cycle_detection.hpp"
#include "random/engine.hpp"
#include "random/random_perm.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;

template <bool directed> void bipartite(int n, int m) {
  odd_cycle_detection<directed> detector(n);
  int l = uniform(1, n - 1);
  auto p = random_perm(n);
  for (int i = 0; i < m; i++) {
    int u = uniform(0, l - 1);
    int v = uniform(l, n - 1);
    if (uniform_bool()) swap(u, v);
    detector.add_edge(p[u], p[v]);
  }
  assert(!detector.detect());
  assert(detector.len == 0);
  assert(detector.vertices.empty());
  assert(detector.edges.empty());
}
void bipartite_small_sparse() {
  int n = uniform(2, 100);
  int m = uniform(0, 100);
  bipartite<true>(n, m);
  bipartite<false>(n, m);
}
void bipartite_small_dense() {
  int n = uniform(2, 100);
  int m = uniform(0, 20000);
  bipartite<true>(n, m);
  bipartite<false>(n, m);
}
void bipartite_large_sparse() {
  int n = uniform(2, 100000);
  int m = uniform(0, 100000);
  bipartite<true>(n, m);
  bipartite<false>(n, m);
}

template <bool directed> void has_odd_cycle(int n, int m) {
  int k = 2 * uniform(0, min(n - 1, m - 1) / 2) + 1;
  std::vector<std::pair<int, int>> edges;
  auto p = random_perm(n);
  for (int i = 0; i < k; i++) {
    int u = p[i];
    int v = p[(i + 1) % k];
    if (!directed && uniform_bool()) swap(u, v);
    edges.emplace_back(u, v);
  }
  for (int i = 0; i < m - k; i++) {
    int u = uniform(0, n - 1);
    int v = uniform(0, n - 1);
    edges.emplace_back(u, v);
  }
  shuffle(edges);
  odd_cycle_detection<directed> detector(n);
  for (auto [u, v] : edges) detector.add_edge(u, v);
  assert(detector.detect());
  int cycle_len = detector.len;
  auto& cycle_v = detector.vertices;
  auto& cycle_e = detector.edges;
  assert(!cycle_v.empty());
  assert(int(cycle_v.size()) == cycle_len);
  assert(int(cycle_e.size()) == cycle_len);
  assert(cycle_v.size() % 2 == 1);
  for (int i = 0; i < cycle_len; i++) {
    int u = cycle_v[i];
    int v = cycle_v[(i + 1) % cycle_len];
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    int id = cycle_e[i];
    assert(0 <= id && id < int(edges.size()));
    int eu = edges[id].first;
    int ev = edges[id].second;
    assert((u == eu && v == ev) || (u == ev && v == eu));
  }
  std::sort(cycle_v.begin(), cycle_v.end());
  assert(std::unique(cycle_v.begin(), cycle_v.end()) == cycle_v.end());
  std::sort(cycle_e.begin(), cycle_e.end());
  assert(std::unique(cycle_e.begin(), cycle_e.end()) == cycle_e.end());
}
void has_odd_cycle_small_sparse() {
  int n = uniform(2, 100);
  int m = uniform(0, 100);
  has_odd_cycle<true>(n, m);
  has_odd_cycle<false>(n, m);
}
void has_odd_cycle_small_dense() {
  int n = uniform(2, 100);
  int m = uniform(0, 20000);
  has_odd_cycle<true>(n, m);
  has_odd_cycle<false>(n, m);
}
void has_odd_cycle_large_sparse() {
  int n = uniform(2, 100000);
  int m = uniform(0, 100000);
  has_odd_cycle<true>(n, m);
  has_odd_cycle<false>(n, m);
}

template <bool directed> void no_edge() {
  for (int i = 0; i <= 10; i++) {
    odd_cycle_detection<directed> detector(i);
    assert(!detector.detect());
    assert(detector.len == 0);
    assert(detector.vertices.empty());
    assert(detector.edges.empty());
  }
}

int main() {
  for (int i = 0; i < 5000; i++) {
    bipartite_small_sparse();
    has_odd_cycle_small_sparse();
  }
  for (int i = 0; i < 20; i++) {
    bipartite_small_dense();
    has_odd_cycle_small_dense();
  }
  for (int i = 0; i < 5; i++) {
    bipartite_large_sparse();
    has_odd_cycle_large_sparse();
  }
  no_edge<true>();
  no_edge<false>();
  cout << "Hello World\n";
}