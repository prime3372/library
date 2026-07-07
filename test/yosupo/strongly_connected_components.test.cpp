#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "graph/strongly_connected_components.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  strongly_connected_components g(n);
  rep(i, 0, m) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b);
  }
  auto scc = g.build().scc;
  cout << scc.size() << "\n";
  for (auto vs : scc) {
    cout << vs.size() << " ";
    for (int v : vs) cout << v << " ";
    cout << "\n";
  }
}