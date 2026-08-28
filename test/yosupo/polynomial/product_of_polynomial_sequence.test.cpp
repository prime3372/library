#define PROBLEM "https://judge.yosupo.jp/problem/product_of_polynomial_sequence"

#include "poly/formal_power_series.hpp"
#include "poly/fps_prod.hpp"
#include "util/static_modint.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using mint = modint998244353;
using fps = formal_power_series<mint>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<formal_power_series<mint>> f(n);
  for (int i = 0; i < n; i++) {
    int d;
    cin >> d;
    f[i].resize(d + 1);
    cin >> f[i];
  }
  cout << prod(f) << "\n";
}