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
  for (auto& v : a) {
    for (auto& x : v) cin >> x;
  }
  for (auto& v : b) {
    for (auto& x : v) cin >> x;
  }
  a *= b;
  for (auto& v : a) {
    for (auto& x : v) cout << x << " ";
    cout << "\n";
  }
}