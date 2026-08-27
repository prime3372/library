#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"

#include "setfunc/xor_convolution.hpp"
#include "util/static_modint.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  cin >> n;
  vector<mint> a(1 << n), b(1 << n);
  for (mint& ai : a) cin >> ai;
  for (mint& bi : b) cin >> bi;
  auto ans = xor_convolution(n, a, b);
  for (mint& x : ans) cout << x << " ";
}