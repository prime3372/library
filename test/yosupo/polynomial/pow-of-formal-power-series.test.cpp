#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "poly/formal-power-series.hpp"
#include "poly/pow-of-formal-power-series.hpp"
#include "util/static-modint.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using mint = modint998244353;
using fps = formal_power_series<mint>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  long long m;
  cin >> n >> m;
  fps f(n);
  for (mint& x : f) cin >> x;
  auto g = pow(f, m);
  for (mint& x : g) cout << x << " ";
}