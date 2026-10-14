#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include "graph/two-edge-connected-components.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  TwoEdgeConnectedComponents g(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b);
  }
  g.build();
  cout << g.group_num << "\n";
  for (auto group : g.groups) {
    cout << group.size() << " ";
    for (auto v : group) cout << v << " ";
    cout << "\n";
  }
}