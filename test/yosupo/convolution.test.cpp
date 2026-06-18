#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../poly/convolution.hpp"
#include "../../util/static_modint.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using mint = modint998244353;

int main() {
  int n, m;
  cin >> n >> m;
  vector<mint> a(n), b(m);
  rep(i, 0, n) cin >> a[i];
  rep(i, 0, m) cin >> b[i];
  auto c = convolution(a, b);
  for (auto ci : c) cout << ci << " ";
}
