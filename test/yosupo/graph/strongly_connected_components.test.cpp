#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "graph/strongly_connected_components.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  strongly_connected_components scc(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    scc.add_edge(a, b);
  }
  scc.build();
  cout << scc.group_num << "\n";
  for (auto vs : scc.groups) {
    cout << vs.size() << " ";
    for (int v : vs) cout << v << " ";
    cout << "\n";
  }
}