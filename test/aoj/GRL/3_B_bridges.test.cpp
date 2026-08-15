#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_3_B"

#include "graph/two_edge_connected_components.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < int(b); i++)
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  two_edge_connected_components g(n);
  vector<pair<int, int>> edges;
  rep(i, 0, m) {
    int s, t;
    cin >> s >> t;
    if (s > t) swap(s, t);
    g.add_edge(s, t);
    edges.emplace_back(s, t);
  }
  g.build();
  sort(edges.begin(), edges.end());
  rep(i, 0, m) {
    auto [u, v] = edges[i];
    if (g.id[u] != g.id[v]) cout << u << " " << v << "\n";
  }
}