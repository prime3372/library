#define PROBLEM "https://judge.yosupo.jp/problem/minimum_spanning_tree"

#include "graph/kruscal.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  kruscal<ll> g(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    ll c;
    cin >> a >> b >> c;
    g.add_edge(a, b, c);
  }
  cout << g.min() << "\n";
  auto mst = g.mst();
  for (int e : mst) cout << e << " ";
}