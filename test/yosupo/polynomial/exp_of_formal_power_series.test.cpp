#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include "poly/formal_power_series.hpp"
#include "poly/fps_exp.hpp"
#include "util/static_modint.hpp"
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
  cin >> f;
  cout << exp(f) << " ";
}