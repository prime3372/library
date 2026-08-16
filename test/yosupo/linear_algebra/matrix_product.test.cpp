#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

#include "linalg/matrix.hpp"
#include "util/static_modint.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, k;
  cin >> n >> m >> k;
  matrix<mint> a(n, m), b(m, k);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < k; j++) {
      cin >> b[i][j];
    }
  }
  a *= b;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      cout << a[i][j] << " ";
    }
    cout << "\n";
  }
}