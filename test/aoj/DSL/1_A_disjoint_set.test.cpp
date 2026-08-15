#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_1_A"

#include "ds/union_find.hpp"

#include <bits/stdc++.h>
using namespace std;
using namespace cp;

int main() {
  int n, q;
  cin >> n >> q;
  union_find uf(n);
  while (q--) {
    int com, x, y;
    cin >> com >> x >> y;
    if (com == 0) {
      uf.unite(x, y);
    } else {
      cout << uf.same(x, y) << "\n";
    }
  }
}