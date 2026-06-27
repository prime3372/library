#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include "cumsum.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  cumsum<ll> cum(n);
  rep(i, 0, n) cin >> cum[i];
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << cum.sum(l, r) << "\n";
  }
}
