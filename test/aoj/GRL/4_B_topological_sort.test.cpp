#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/GRL_4_B"

#include "graph/topological_sort.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < int(b); i++)
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int v, e;
  cin >> v >> e;
  vector<vector<int>> adj(v);
  rep(i, 0, e) {
    int s, t;
    cin >> s >> t;
    adj[s].push_back(t);
  }
  auto res = topological_sort(adj);
  rep(i, 0, v) cout << res[i] << "\n";
}