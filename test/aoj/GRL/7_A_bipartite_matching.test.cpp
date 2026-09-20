#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_7_A"

#include "graph/bipartite_matching.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int x, y, m;
  cin >> x >> y >> m;
  bipartite_matching bm(x, y);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    bm.add_edge(u, v);
  }
  int ans = bm.max_matching();
  auto edges = bm.edges();
  assert(int(edges.size()) == ans);
  vector<bool> chosen_x(x), chosen_y(y);
  for (auto [u, v] : edges) {
    assert(0 <= u && u < x);
    assert(0 <= v && v < y);
    assert(!chosen_x[u] && !chosen_y[v]);
    chosen_x[u] = chosen_y[v] = true;
  }
  cout << ans << "\n";
}