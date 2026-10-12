#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include "poly/formal-power-series.hpp"
#include "poly/exp-of-formal-power-series.hpp"
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
  cin >> n;
  fps f(n);
  for (mint& x : f) cin >> x;
  auto g = exp(f);
  for (mint& x : g) cout << x << " ";
}