#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include "../../graph/dijkstra.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  dijkstra<ll> g(n);
  rep(i, 0, m) {
    int a, b;
    ll c;
    cin >> a >> b >> c;
    g.add_edge(a, b, c);
  }
  g.search(s);
  if (g.dist(t) == -1) {
    cout << -1 << "\n";
    return 0;
  }
  auto p = g.route(t).first;
  cout << g.dist(t) << " " << p.size() - 1 << "\n";
  for (int i = 0; i < int(p.size()) - 1; i++) {
    cout << p[i] << " " << p[i + 1] << "\n";
  }
}
