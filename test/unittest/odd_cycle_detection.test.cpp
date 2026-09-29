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

template <bool directed> void has_odd_cycle(int n, int m) {
  int k = 2 * uniform(0, min(n - 1, m - 1) / 2) + 1;
  auto p = random_perm(n);
  std::vector<std::pair<int, int>> edges;
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
    int e_id = cycle_e[i];
    assert(0 <= e_id && e_id < int(edges.size()));
    int eu = edges[e_id].first;
    int ev = edges[e_id].second;
    assert((u == eu && v == ev) || (u == ev && v == eu));
  }
  std::sort(cycle_v.begin(), cycle_v.end());
  assert(std::unique(cycle_v.begin(), cycle_v.end()) == cycle_v.end());
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

void dag(int n, int m) {
  odd_cycle_detection<true> detector(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    do {
      u = uniform(0, n - 1);
      v = uniform(0, n - 1);
    } while (u == v);
    if (u > v) swap(u, v);
    detector.add_edge(u, v);
  }
  assert(!detector.detect());
  assert(detector.len == 0);
  assert(detector.vertices.empty());
  assert(detector.edges.empty());
}
void dag_small_sparse() {
  int n = uniform(2, 100);
  int m = uniform(0, 100);
  dag(n, m);
}
void dag_small_dense() {
  int n = uniform(2, 100);
  int m = uniform(0, 20000);
  dag(n, m);
}
void dag_large_sparse() {
  int n = uniform(2, 100000);
  int m = uniform(0, 100000);
  dag(n, m);
}

void bipartite_in_dag(int n1, int m1, int n2, int m2) {
  int n = n1 * n2;
  odd_cycle_detection<true> detector(n);
  auto p = random_perm(n);
  for (int i = 0; i < n1; i++) {
    int l = uniform(1, n2 - 1);
    for (int j = 0; j < m2; j++) {
      int u = uniform(0, l - 1) + n2 * i;
      int v = uniform(l, n2 - 1) + n2 * i;
      if (uniform_bool()) swap(u, v);
      detector.add_edge(p[u], p[v]);
    }
  }
  for (int i = 0; i < m1; i++) {
    int u, v;
    do {
      u = uniform(0, n - 1);
      v = uniform(0, n - 1);
    } while (u / n2 == v / n2);
    if (u > v) swap(u, v);
    detector.add_edge(p[u], p[v]);
  }
  assert(!detector.detect());
  assert(detector.len == 0);
  assert(detector.vertices.empty());
  assert(detector.edges.empty());
}
void bipartite_in_dag_small_sparse() {
  int n1 = uniform(2, 10);
  int m1 = uniform(0, 100);
  int n2 = uniform(2, 10);
  int m2 = uniform(0, 10);
  bipartite_in_dag(n1, m1, n2, m2);
}
void bipartite_in_dag_small_dense() {
  int n1 = uniform(2, 10);
  int m1 = uniform(0, 20000);
  int n2 = uniform(2, 10);
  int m2 = uniform(0, 200);
  bipartite_in_dag(n1, m1, n2, m2);
}
void bipartite_in_dag_large_sparse() {
  int n1 = uniform(2, 100);
  int m1 = uniform(0, 100000);
  int n2 = uniform(2, 100);
  int m2 = uniform(0, 100);
  bipartite_in_dag(n1, m1, n2, m2);
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
    has_odd_cycle_small_sparse();
    bipartite_small_sparse();
    dag_small_sparse();
    bipartite_in_dag_small_sparse();
  }
  for (int i = 0; i < 20; i++) {
    has_odd_cycle_small_dense();
    bipartite_small_dense();
    dag_small_dense();
    bipartite_in_dag_small_dense();
  }
  for (int i = 0; i < 5; i++) {
    has_odd_cycle_large_sparse();
    bipartite_large_sparse();
    dag_large_sparse();
    bipartite_in_dag_large_sparse();
  }
  no_edge<true>();
  no_edge<false>();
  cout << "Hello World\n";
}