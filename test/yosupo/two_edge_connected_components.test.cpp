#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"

#include "graph/two_edge_connected_components.hpp"

#include <bits/stdc++.h>
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  two_edge_connected_components g(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b);
  }
  auto groups = g.build().groups;
  cout << groups.size() << "\n";
  for (auto group : groups) {
    cout << group.size() << " ";
    for (auto v : group) cout << v << " ";
    cout << "\n";
  }
}