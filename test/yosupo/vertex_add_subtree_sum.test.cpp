#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include "../../ds/fenwick_tree.hpp"
#include "../../tree/hl_decomposition.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  std::vector<ll> a(n);
  hl_decomposition hld(n);
  rep(i, 0, n) cin >> a[i];
  rep(i, 1, n) {
    int p;
    cin >> p;
    hld.add_edge(i, p);
  }
  hld.build();
  auto par = hld.parent, in = hld.in, out = hld.out;
  fenwick_tree<ll> fw(n);
  rep(i, 0, n) fw.add(in[i], a[i]);
  while (q--) {
    bool t;
    cin >> t;
    if (!t) {
      int p;
      ll x;
      cin >> p >> x;
      fw.add(in[p], x);
    } else {
      int u;
      cin >> u;
      cout << fw.sum(in[u], out[u]) << "\n";
    }
  }
}
