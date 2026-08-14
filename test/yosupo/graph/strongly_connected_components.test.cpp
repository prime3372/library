#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include "graph/strongly_connected_components.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < int(b); i++)
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  strongly_connected_components scc(n);
  rep(i, 0, m) {
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