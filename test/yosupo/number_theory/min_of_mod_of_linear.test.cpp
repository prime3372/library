#define PROBLEM "https://judge.yosupo.jp/problem/min_of_mod_of_linear"

#include "number/floor_sum.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    ll n, m, a, b;
    cin >> n >> m >> a >> b;
    ll l = 0, r = m;
    while (r - l > 1) {
      ll mid = (l + r) / 2;
      if (floor_sum(n, m, a, b) == floor_sum(n, m, a, b - mid)) {
        l = mid;
      } else {
        r = mid;
      }
    }
    cout << l << "\n";
  }
}