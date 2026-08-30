#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_A"

#include "ds/segtree.hpp"
#include <climits>
#include <iostream>

using namespace std;
using namespace cp;

int op(int x, int y) { return min(x, y); }
int e() { return INT_MAX; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  segtree<int, op, e> seg(n);
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