#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"

#include "../../util/static_modint.hpp"
#include "../../setfunc/and_convolution.hpp"
#include <bits/stdc++.h>

using namespace std;
using mint = modint998244353;

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  cin >> n;
  vector<mint> a(1 << n), b(1 << n);
  for (int i = 0; i < (1 << n); i++) {
    int a_i;
    cin >> a_i;
    a[i] = a_i;
  }
  for (int i = 0; i < (1 << n); i++) {
    int b_i;
    cin >> b_i;
    b[i] = b_i;
  }
  for (mint x : and_convolution(n, a, b)) cout << x.val() << " ";
}
