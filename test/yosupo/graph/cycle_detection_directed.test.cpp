#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"

#include "graph/cycle_detection.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  cycle_detection<true> cycle(n);
  for (int i = 0; i < m; i++) {
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
  for (int e : cycle.edges) cout << e << "\n";
}