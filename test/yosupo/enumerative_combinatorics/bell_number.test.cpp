#define PROBLEM "https://judge.yosupo.jp/problem/bell_number"

#include "comb/bell.hpp"
#include "util/static_modint.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  auto b = bell<mint>(n);
  for (mint& x : b) cout << x << " ";
}