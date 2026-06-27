#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"

#include "../../linalg/matrix.hpp"
#include "../../util/static_modint.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using ll = long long;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  ll k;
  cin >> n >> k;
  matrix<Add_Mul<mint>> a(n, n);
  rep(i, 0, n) rep(j, 0, n) cin >> a[i][j];
  auto b = a.pow(k);
  rep(i, 0, n) {
    rep(j, 0, n) {
      cout << b[i][j] << " ";
    }
    cout << "\n";
  }
}
