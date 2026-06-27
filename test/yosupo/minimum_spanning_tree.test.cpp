#define PROBLEM "https://judge.yosupo.jp/problem/minimum_spanning_tree"

#include "../../graph/kruscal.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  kruscal<ll> g(n);
  rep(i, 0, m) {
    int a, b;
    ll c;
    cin >> a >> b >> c;
    g.add_edge(a, b, c);
  }
  cout << g.min() << "\n";
  auto mst = g.mst();
  rep(i, 0, n - 1) cout << mst[i] << " ";
}
