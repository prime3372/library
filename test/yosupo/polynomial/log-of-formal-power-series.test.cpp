#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"

#include "poly/formal-power-series.hpp"
#include "poly/log-of-formal-power-series.hpp"
#include "util/static-modint.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  FormalPowerSeries<mint> f(n);
  for (mint& x : f) cin >> x;
  auto g = log(f);
  for (mint& x : g) cout << x << " ";
}