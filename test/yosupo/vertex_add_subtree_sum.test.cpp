#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include "../../ds/fenwick_tree.hpp"
#include "../../tree/euler_tour.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  std::vector<ll> a(n);
  rep(i, 0, n) cin >> a[i];
  euler_tour et(n);
  rep(i, 1, n) {
    int p;
    cin >> p;
    et.add_edge(i, p);
  }
  et.build();
  auto in = et.in, out = et.out;
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
