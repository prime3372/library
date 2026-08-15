#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/GRL/all/GRL_6_A"

#include "graph/max_flow.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < int(b); i++)
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  max_flow<int> mf(n);
  rep(i, 0, m) {
    int u, v, c;
    cin >> u >> v >> c;
    mf.add_edge(u, v, c);
  }
  cout << mf.flow(0, n - 1) << "\n";
}