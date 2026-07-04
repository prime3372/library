#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include "tree/tree_diameter.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  tree_diameter<ll> diam(n);
  rep(i, 0, n - 1) {
    int a, b, c;
    cin >> a >> b >> c;
    diam.add_edge(a, b, c);
  }
  diam.build();
  cout << diam.dist << " " << diam.vertices.size() << "\n";
  for (int v : diam.vertices) cout << v << " ";
}