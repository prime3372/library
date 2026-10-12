#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_Matrix"

#include "linalg/matrix.hpp"
#include "util/static-modint.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  ll k;
  cin >> n >> k;
  Matrix<mint> a(n, n);
  for (auto& v : a) {
    for (auto& x : v) cin >> x;
  }
  auto b = a.pow(k);
  for (auto& v : b) {
    for (auto& x : v) cout << x << " ";
    cout << "\n";
  }
}