#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "random/engine.hpp"
#include "random/random_graph.hpp"
#include "ds/union_find.hpp"
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

void complete() {
  int n = uniform(1, 100);
  int m = n * (n - 1) / 2;
  auto edges = random_graph<false, true, true, false>(n, n * (n - 1) / 2);
  assert(int(edges.size()) == m);
  vector<vector<bool>> exist(n, vector<bool>(n));
  for (auto [u, v] : edges) {
    assert(1 <= u && u <= n);
    assert(1 <= v && v <= n);
    if (u > v) swap(u, v);
    u--, v--;
    assert(!exist[u][v]);
    exist[u][v] = true;
  }
}

void undirected_simple_connected() {
  int n = uniform(1, 100);
  int m = uniform(n - 1, n * (n - 1) / 2);
  auto edges = random_graph<false, true, true, true>(n, m);
  assert(int(edges.size()) == m);
  for (auto& [u, v] : edges) {
    assert(1 <= u && u <= n);
    assert(1 <= v && v <= n);
    assert(u != v);
    if (u > v) swap(u, v);
  }
  sort(edges.begin(), edges.end());
  for (int i = 0; i < int(edges.size()) - 1; i++) {
    assert(edges[i] != edges[i + 1]);
  }
  union_find uf(n);
  for (auto [u, v] : edges) uf.unite(u - 1, v - 1);
  assert(uf.groups().size() == 1);
}

void directed_simple() {
  int n = uniform(1, 100);
  int m = uniform(n - 1, n * (n - 1) / 2);
  auto edges = random_graph<false, true, true, false>(n, m);
  assert(int(edges.size()) == m);
  for (auto& [u, v] : edges) {
    assert(1 <= u && u <= n);
    assert(1 <= v && v <= n);
    assert(u != v);
  }
  sort(edges.begin(), edges.end());
  for (int i = 0; i < int(edges.size()) - 1; i++) {
    assert(edges[i] != edges[i + 1]);
  }
}

void reachable_from_s() {
  int n = uniform(1, 100);
  int m = uniform(n - 1, 100);
  int s = uniform(0, n - 1);
  auto edges = random_graph<true, false, false, true>(n, m, s);
  assert(int(edges.size()) == m);
  vector<vector<int>> g(n);
  for (auto [u, v] : edges) {
    assert(1 <= u && u <= n);
    assert(1 <= v && v <= n);
    u--, v--;
    g[u].push_back(v);
  }
  vector<bool> reached(n);
  auto dfs = [&](auto self, int v) -> void {
    assert(0 <= v && v < n);
    reached[v] = true;
    for (auto nv : g[v]) {
      if (!reached[nv]) self(self, nv);
    }
  };
  dfs(dfs, s);
  for (int i = 0; i < n; i++) assert(reached[i]);
}

void empty() { assert(random_graph(0, 0).empty()); }

int main() {
  for (int i = 0; i < 1000; i++) complete();
  for (int i = 0; i < 1000; i++) undirected_simple_connected();
  for (int i = 0; i < 1000; i++) directed_simple();
  for (int i = 0; i < 1000; i++) reachable_from_s();
  empty();
  cout << "Hello World\n";
}