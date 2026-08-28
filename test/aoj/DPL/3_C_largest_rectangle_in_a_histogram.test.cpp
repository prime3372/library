#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_3_C"

#include "ds/cartesian_tree.hpp"
#include <algorithm>
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
  cartesian_tree cart(a);
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans = max(ans, a[i] * cart.size[i]);
  }
  cout << ans << "\n";
}