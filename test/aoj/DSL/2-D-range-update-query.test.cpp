#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_D"

#include "ds/lazy-segment-tree.hpp"
#include <climits>
#include <iostream>

using namespace std;
using namespace cp;

int op(int x, int y) { return min(x, y); }
int e() { return INT_MAX; }
int mapping(int f, int x) { return f == -1 ? x : f; }
int composition(int g, int f) { return g == -1 ? f : g; }
int id() { return -1; }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  LazySegmentTree<int, op, e, int, mapping, composition, id> seg(n);
  while (q--) {
    int com;
    cin >> com;
    if (com == 0) {
      int s, t, x;
      cin >> s >> t >> x;
      seg.apply(s, t + 1, x);
    } else {
      int i;
      cin >> i;
      cout << seg[i] << "\n";
    }
  }
}