#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_1_B"

#include "ds/weighted_union_find.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  int n, q;
  cin >> n >> q;
  weighted_union_find<int> uf(n);
  while (q--) {
    int com;
    cin >> com;
    if (com == 0) {
      int x, y, z;
      cin >> x >> y >> z;
      uf.unite(y, x, z);
    } else {
      int x, y;
      cin >> x >> y;
      if (!uf.same(x, y)) {
        cout << "?" << "\n";
      } else {
        cout << uf.diff(y, x) << "\n";
      }
    }
  }
}