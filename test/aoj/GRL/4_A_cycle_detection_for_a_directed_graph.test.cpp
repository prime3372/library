#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_4_A"

#include "graph/cycle_detection.hpp"
#include "graph/topological_sort.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  cycle_detection<true> cycle(n);
  vector<vector<int>> adj(n);
  vector<pair<int, int>> edges(m);
  for (int i = 0; i < m; i++) {
    int s, t;
    cin >> s >> t;
    cycle.add_edge(s, t);
    adj[s].push_back(t);
    edges[i] = {s, t};
  }
  bool ans = cycle.detect();
  if (!ans) {
    assert(!topological_sort(adj).empty());
    cout << ans << "\n";
    return 0;
  }
  auto& v = cycle.vertices;
  auto& e = cycle.edges;
  assert(v.size() == e.size());
  for (int i = 0; i < int(e.size()); i++) {
    assert(0 <= e[i] && e[i] < m);
    assert(edges[e[i]] == make_pair(v[i], v[(i + 1) % e.size()]));
  }
  cout << ans << "\n";
}