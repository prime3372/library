#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "../../graph/scc_graph.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  scc_graph g(n);
  rep(i, 0, m) {
    int a, b;
    cin >> a >> b;
    g.add_edge(a, b);
  }
  auto scc = g.scc();
  cout << scc.size() << "\n";
  for (auto vs : scc) {
    cout << vs.size() << " ";
    for (int v : vs) cout << v << " ";
    cout << "\n";
  }
}
