#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"

#include "poly/formal_power_series.hpp"
#include "util/static_modint.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  formal_power_series<mint> f(n);
  rep(i, 0, n) cin >> f[i];
  cout << f.log() << "\n";
}