#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_B"

#include "ds/fenwick_tree.hpp"

#include <bits/stdc++.h>
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  fenwick_tree<int> fw(n);
  while (q--) {
    int com, x, y;
    cin >> com >> x >> y;
    if (com == 0) {
      fw.add(x - 1, y);
    } else {
      cout << fw.sum(x - 1, y) << "\n";
    }
  }
}
