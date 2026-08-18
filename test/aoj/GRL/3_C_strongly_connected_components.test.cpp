#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_3_C"

#include "graph/strongly_connected_components.hpp"
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
  strongly_connected_components scc(n);
  for (int i = 0; i < m; i++) {
    int s, t;
    cin >> s >> t;
    scc.add_edge(s, t);
  }
  scc.build();
  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << (scc.id[u] == scc.id[v]) << "\n";
  }
}