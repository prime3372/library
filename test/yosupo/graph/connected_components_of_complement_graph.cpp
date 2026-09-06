#define PROBLEM "https://judge.yosupo.jp/problem/connected_components_of_complement_graph"

#include "graph/complement_connected_components.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  complement_connected_components cc(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    cc.add_edge(a, b);
  }
  auto ans = cc.calc();
  cout << ans.size() << "\n";
  for (auto& vs : ans) {
    cout << vs.size() << " ";
    for (int v : vs) cout << v << " ";
    cout << "\n";
  }
}