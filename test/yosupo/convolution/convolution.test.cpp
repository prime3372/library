#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "poly/convolution.hpp"
#include "util/static_modint.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<mint> a(n), b(m);
  for (auto& ai : a) cin >> ai;
  for (auto& bi : b) cin >> bi;
  auto c = convolution(a, b);
  for (auto ci : c) cout << ci << " ";
}