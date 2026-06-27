#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "../../ds/fenwick_tree.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  fenwick_tree<ll> fw(n);
  rep(i, 0, n) {
    ll a;
    cin >> a;
    fw.add(i, a);
  }
  while (q--) {
    bool t;
    cin >> t;
    if (!t) {
      int p;
      ll x;
      cin >> p >> x;
      fw.add(p, x);
    } else {
      int l, r;
      cin >> l >> r;
      cout << fw.sum(l, r) << "\n";
    }
  }
}
