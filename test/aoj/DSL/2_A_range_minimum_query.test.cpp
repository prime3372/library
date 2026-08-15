#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include "algebra/min.hpp"
#include "ds/segtree.hpp"

#include <bits/stdc++.h>
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  segtree<alg::min<int, INT_MAX>> seg(n);
  while (q--) {
    int com, x, y;
    cin >> com >> x >> y;
    if (com == 0) {
      seg.set(x, y);
    } else {
      cout << seg.prod(x, y + 1) << "\n";
    }
  }
}