#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_3_C"

#include "ds/cartesian_tree.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  int n;
  cin >> n;
  vector<ll> a(n);
  for (auto& ai : a) cin >> ai;
  cartesian_tree<false> cart(a);
  vector<int> sub(n);
  auto dfs = [&](auto self, int v) -> int {
    if (v == -1) return 0;
    sub[v] = 1;
    sub[v] += self(self, cart.left[v]);
    sub[v] += self(self, cart.right[v]);
    return sub[v];
  };
  dfs(dfs, cart.root);
  ll ans = 0;
  for (int i = 0; i < n; i++) ans = max(ans, a[i] * sub[i]);
  cout << ans << "\n";
}