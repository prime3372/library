#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

#include "linalg/matrix.hpp"
#include "util/static_modint.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, k;
  cin >> n >> m >> k;
  matrix<mint> a(n, m), b(m, k);
  cin >> a >> b;
  a *= b;
  cout << a << "\n";
}