#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include "graph/dijkstra.hpp"
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  dijkstra<ll> g(n);
  vector<pair<int, int>> edges(m);
  for (int i = 0; i < m; i++) {
    int a, b;
    ll c;
    cin >> a >> b >> c;
    g.add_edge(a, b, c);
    edges[i] = {a, b};
  }
  g.init(s);
  if (g.dist(t) == -1) {
    cout << -1 << "\n";
    return 0;
  }
  auto [v, e] = g.route(t);
  cout << g.dist(t) << " " << v.size() - 1 << "\n";
  for (int i = 0; i < int(v.size()) - 1; i++) {
    cout << v[i] << " " << v[i + 1] << "\n";
    auto ei = make_pair(v[i], v[i + 1]);
    assert(edges[e[i]] == ei);
  }
}