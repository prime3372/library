#define PROBLEM \
  "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind_fixed_k"

#include "comb/stirling_second_kind_fixed_k.hpp"
#include "util/static_modint.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, k;
  cin >> n >> k;
  auto s = stirling_second_kind_fixed_k<mint>(k, n);
  for (mint& x : s) cout << x << " ";
}