#define PROBLEM "https://judge.yosupo.jp/problem/predecessor_problem"

#include "../../algebra/Max.hpp"
#include "../../ds/segtree.hpp"
#include <bits/stdc++.h>

#define rep(i, a, b) for (int i = int(a); i < int(b); i++)
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  segtree<Max<bool, false>> seg(n);
  rep(i, 0, n) {
    char ti;
    cin >> ti;
    seg.set(i, ti == '1');
  }
  auto f = [](bool i) -> bool { return !i; };
  while (q--) {
    int c;
    cin >> c;
    int k;
    cin >> k;
    if (c == 0) {
      if (!seg[k]) seg.set(k, true);
    } else if (c == 1) {
      if (seg[k]) seg.set(k, false);
    } else if (c == 2) {
      cout << seg[k] << "\n";
    } else if (c == 3) {
      int mr = seg.max_right(k, f);
      cout << (mr == n ? -1 : mr) << "\n";
    } else {
      int ml = seg.min_left(k + 1, f);
      cout << ml - 1 << "\n";
    }
  }
}