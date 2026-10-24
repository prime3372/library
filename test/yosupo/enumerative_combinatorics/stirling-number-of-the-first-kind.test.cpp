#define PROBLEM \
  "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind"

#include "comb/stirling-first-kind.hpp"
#include "util/static-modint.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using mint = modint998244353;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  auto s = signed_stirling_first_kind<mint>(n);
  for (mint& x : s) cout << x << " ";
}