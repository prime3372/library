#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection_undirected"

#include "../../graph/cycle_detection.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  cycle_detection<false> cycle(n);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v;
    cycle.add_edge(u, v);
  }
  cycle.detect();
  if (cycle.len == 0) {
    cout << -1 << "\n";
    return 0;
  }
  cout << cycle.len << "\n";
  for (int v : cycle.vertices) cout << v << " ";
  cout << "\n";
  for (int e : cycle.edges) cout << e << " ";
  cout << "\n";
}
