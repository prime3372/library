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
  for (int i = 0; i < m; ++i) {
    int u = p[uniform(0, l - 1)];
    int v = p[uniform(l, n - 1)];
    detector.add_edge(u, v);
  }
  assert(!detector.detect());
  assert(detector.len == 0);
  assert(detector.vertices.empty());
  assert(detector.edges.empty());
}
void bipartite_small() {
  int n = uniform(2, 100);
  int m = uniform(0, 100);
  bipartite(n, m);
}
void bipartite_dense() {
  int n = uniform(2, 100);
  int m = uniform(0, 100000);
  bipartite(n, m);
}
void bipartite_sparse() {
  int n = uniform(2, 100000);
  int m = uniform(0, 100000);
  bipartite(n, m);
}

void has_odd_cycle(int n, int m) {
  int k = 2 * uniform(0, min(n - 1, m - 1) / 2) + 1;
  auto p = random_perm(n);
  std::vector<std::pair<int, int>> edges;
  for (int i = 0; i < k; i++) {
    edges.emplace_back(p[i], p[(i + 1) % k]);
  }
  for (int i = 0; i < m - k; i++) {
    int u = uniform(0, n - 1);
    int v = uniform(0, n - 1);
    edges.emplace_back(u, v);
  }
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
void has_odd_cycle_small() {
  int n = uniform(1, 100);
  int m = uniform(1, 100);
  has_odd_cycle(n, m);
}
void has_odd_cycle_dense() {
  int n = uniform(1, 100);
  int m = uniform(1, 100000);
  has_odd_cycle(n, m);
}
void has_odd_cycle_sparse() {
  int n = uniform(1, 100000);
  int m = uniform(1, 100000);
  has_odd_cycle(n, m);
}

void empty() {
  odd_cycle_detection detector(0);
  assert(!detector.detect());
  assert(detector.len == 0);
  assert(detector.vertices.empty());
  assert(detector.edges.empty());
}

int main() {
  for (int i = 0; i < 50000; i++) {
    bipartite_small();
    has_odd_cycle_small();
  }
  for (int i = 0; i < 5; i++) {
    bipartite_dense();
    bipartite_sparse();
    has_odd_cycle_dense();
    has_odd_cycle_sparse();
  }
  empty();
  cout << "Hello World\n";
}