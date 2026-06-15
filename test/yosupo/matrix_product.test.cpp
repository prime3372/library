#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

#include "../../linalg/matrix.hpp"
#include "../../util/static_modint.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using mint = modint998244353;

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  matrix<mint> a(n, m), b(m, k);
  rep(i, 0, n) rep(j, 0, m) cin >> a[i][j];
  rep(i, 0, m) rep(j, 0, k) cin >> b[i][j];
  a *= b;
  rep(i, 0, n) {
    rep(j, 0, k) {
      cout << a[i][j] << " ";
    }
    cout << "\n";
  }
}