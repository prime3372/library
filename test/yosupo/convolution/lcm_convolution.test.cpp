#define PROBLEM "https://judge.yosupo.jp/problem/gcd_convolution"

#include "number/lcm_convolution.hpp"
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
  vector<mint> a(n + 1), b(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 1; i <= n; i++) cin >> b[i];
  auto c = lcm_convolution(a, b);
  for (int i = 1; i <= n; i++) cout << c[i] << " ";
}