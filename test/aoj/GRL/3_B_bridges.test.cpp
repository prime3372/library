#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_3_B"

#include "graph/two_edge_connected_components.hpp"
#include <algorithm>
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
  two_edge_connected_components g(n);
  vector<pair<int, int>> edges;
  for (int i = 0; i < m; i++) {
    int s, t;
    cin >> s >> t;
    if (s > t) swap(s, t);
    g.add_edge(s, t);
    edges.emplace_back(s, t);
  }
  g.build();
  sort(edges.begin(), edges.end());
  for (int i = 0; i < m; i++) {
    auto [u, v] = edges[i];
    if (g.id[u] != g.id[v]) cout << u << " " << v << "\n";
  }
}