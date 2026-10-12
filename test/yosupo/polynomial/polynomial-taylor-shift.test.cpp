#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "poly/formal-power-series.hpp"
#include "poly/taylor-shift.hpp"
#include "util/static-modint.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using mint = modint998244353;
using fps = FormalPowerSeries<mint>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  mint c;
  cin >> n >> c;
  fps f(n);
  for (mint& x : f) cin >> x;
  auto g = taylor_shift(f, c);
  for (mint& x : g) cout << x << " ";
}