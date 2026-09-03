#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_6_A"

#include "graph/max_flow.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  max_flow<int> mf(n);
  for (int i = 0; i < m; i++) {
    int u, v, c;
    cin >> u >> v >> c;
    mf.add_edge(u, v, c);
  }
  cout << mf.flow(0, n - 1) << "\n";
}