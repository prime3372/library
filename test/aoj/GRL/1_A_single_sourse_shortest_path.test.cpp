#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_1_A"

#include "graph/dijkstra.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, r;
  cin >> n >> m >> r;
  dijkstra<int> g(n);
  for (int i = 0; i < m; i++) {
    int s, t, d;
    cin >> s >> t >> d;
    g.add_edge(s, t, d);
  }
  g.init(r);
  for (int i = 0; i < n; i++) {
    int ans = g.dist(i);
    if (ans == -1) cout << "INF\n";
    else cout << ans << "\n";
  }
}