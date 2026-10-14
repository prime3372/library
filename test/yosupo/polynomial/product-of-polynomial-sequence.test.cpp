#define PROBLEM "https://judge.yosupo.jp/problem/product_of_polynomial_sequence"

#include "poly/formal-power-series.hpp"
#include "poly/product-of-polynomial-sequence.hpp"
#include "util/static-modint.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<FormalPowerSeries<mint>> f(n);
  for (int i = 0; i < n; i++) {
    int d;
    cin >> d;
    f[i].resize(d + 1);
    for (mint& x : f[i]) cin >> x;
  }
  auto g = prod(f);
  for (mint& x : g) cout << x << " ";
}