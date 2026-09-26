#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_G"

#include "ds/range_add_range_sum.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  range_add_range_sum<ll> d(n);
  while (q--) {
    int com;
    cin >> com;
    if (com == 0) {
      int s, t;
      ll x;
      cin >> s >> t >> x;
      d.add(s - 1, t, x);
    } else {
      int s, t;
      cin >> s >> t;
      cout << d.sum(s - 1, t) << "\n";
    }
  }
}