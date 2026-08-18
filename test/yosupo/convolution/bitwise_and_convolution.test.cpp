#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"

#include "util/static_modint.hpp"
#include "setfunc/and_convolution.hpp"
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
  for (int i = 0; i < (1 << n); i++) cin >> a[i];  
  for (int i = 0; i < (1 << n); i++) cin >> b[i];  
  auto ans = and_convolution(n, a, b);
  for (const mint& x : ans) cout << x.val() << " ";
}