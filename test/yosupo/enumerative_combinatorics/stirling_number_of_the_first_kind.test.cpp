#define PROBLEM \
  "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind"

#include "comb/stirling_first.hpp"
#include "util/static_modint.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  auto s = stirling_first<mint>(n);
  for (mint& x : s) cout << x << " ";
}