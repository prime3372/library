#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection_undirected"

#include "graph/cycle_detection.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  cycle_detection<false> detector(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    detector.add_edge(u, v);
  }
  if (!detector.detect()) {
    cout << -1 << "\n";
    return 0;
  }
  cout << detector.len << "\n";
  for (int v : detector.vertices) cout << v << " ";
  cout << "\n";
  for (int e : detector.edges) cout << e << " ";
  cout << "\n";
}