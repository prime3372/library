#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include "ds/fenwick_tree.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  fenwick_tree<ll> fw(n);
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    fw.add(i, a);
  }
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int p, x;
      cin >> p >> x;
      fw.add(p, x);
    } else {
      int l, r;
      cin >> l >> r;
      cout << fw.sum(l, r) << "\n";
    }
  }
}