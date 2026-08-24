#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"

#include "graph/cycle_detection.hpp"
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  cycle_detection<true> cycle(n);
  vector<pair<int, int>> edges(m);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    cycle.add_edge(u, v);
    edges[i] = {u, v};
  }
  if (!cycle.detect()) {
    cout << -1 << "\n";
    return 0;
  }
  int len = cycle.len;
  auto& v = cycle.vertices, e = cycle.edges;
  cout << len << "\n";
  for (int i = 0; i < len; i++) {
    assert(edges[e[i]].first == v[i]);
    assert(edges[e[i]].second == v[(i + 1) % len]);
    cout << e[i] << "\n";
  }
}