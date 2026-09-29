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

void bipartite(int n, int m) {
  odd_cycle_detection detector(n);
  int l = uniform(1, n - 1);
  auto p = random_perm(n);
  for (int i = 0; i < m; i++) {
    int u = p[uniform(0, l - 1)];
    int v = p[uniform(l, n - 1)];
    if (uniform_bool()) swap(u, v);
    detector.add_edge(u, v);
  }
  assert(!detector.detect());
  assert(detector.len == 0);
  assert(detector.vertices.empty());
  assert(detector.edges.empty());
}
void bipartite_small_sparse() {
  int n = uniform(2, 100);
  int m = uniform(0, 200);
  bipartite(n, m);
}
void bipartite_small_dense() {
  int n = uniform(2, 100);
  int m = uniform(0, 50000);
  bipartite(n, m);
}
void bipartite_large_sparse() {
  int n = uniform(2, 100000);
  int m = uniform(0, 200000);
  bipartite(n, m);
}

void nonbipartite(int n, int m) {
  int k = 2 * uniform(0, min(n - 1, m - 1) / 2) + 1;
  auto p = random_perm(n);
  std::vector<std::pair<int, int>> edges;
  for (int i = 0; i < k; i++) {
    int u = p[i];
    int v = p[(i + 1) % k];
    if (uniform_bool()) swap(u, v);
    edges.emplace_back(u, v);
  }
  for (int i = 0; i < m - k; i++) {
    int u = uniform(0, n - 1);
    int v = uniform(0, n - 1);
    edges.emplace_back(u, v);
  }
  shuffle(edges);
  odd_cycle_detection detector(n);
  for (auto [u, v] : edges) detector.add_edge(u, v);
  assert(detector.detect());
  int cycle_len = detector.len;
  auto& cycle_v = detector.vertices;
  auto& cycle_e = detector.edges;
  assert(!cycle_v.empty());
  assert(int(cycle_v.size()) == cycle_len);
  assert(int(cycle_e.size()) == cycle_len);
  assert(cycle_v.size() % 2 == 1);
  for (int i = 0; i < cycle_len; ++i) {
    int u = cycle_v[i];
    int v = cycle_v[(i + 1) % cycle_len];
    assert(0 <= u && u < n);
    assert(0 <= v && v < n);
    int e_id = cycle_e[i];
    assert(0 <= e_id && e_id < int(edges.size()));
    int eu = edges[e_id].first;
    int ev = edges[e_id].second;
    assert((u == eu && v == ev) || (u == ev && v == eu));
  }
  std::sort(cycle_v.begin(), cycle_v.end());
  assert(std::unique(cycle_v.begin(), cycle_v.end()) == cycle_v.end());
}
void nonbipartite_small_sparse() {
  int n = uniform(2, 100);
  int m = uniform(0, 200);
  nonbipartite(n, m);
}
void nonbipartite_small_dense() {
  int n = uniform(2, 100);
  int m = uniform(0, 50000);
  nonbipartite(n, m);
}
void nonbipartite_large_sparse() {
  int n = uniform(2, 100000);
  int m = uniform(0, 200000);
  nonbipartite(n, m);
}

void no_edge() {
  for (int i = 0; i <= 10; i++) {
    odd_cycle_detection detector(i);
    assert(!detector.detect());
    assert(detector.len == 0);
    assert(detector.vertices.empty());
    assert(detector.edges.empty());
  }
}

int main() {
  for (int i = 0; i < 10000; i++) {
    bipartite_small_sparse();
    nonbipartite_small_sparse();
  }
  for (int i = 0; i < 50; i++) {
    bipartite_small_dense();
    nonbipartite_small_dense();
  }
  for (int i = 0; i < 5; i++) {
    bipartite_large_sparse();
    nonbipartite_large_sparse();
  }
  no_edge();
  cout << "Hello World\n";
}