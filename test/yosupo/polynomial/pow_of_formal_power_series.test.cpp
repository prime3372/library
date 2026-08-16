#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "poly/formal_power_series.hpp"
#include "util/static_modint.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  long long m;
  cin >> n >> m;
  formal_power_series<mint> f(n);
  for (int i = 0; i < n; i++) cin >> f[i];
  cout << f.pow(m) << "\n";
}