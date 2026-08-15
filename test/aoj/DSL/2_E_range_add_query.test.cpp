#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_E"

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
    int com;
    cin >> com;
    if (com == 0) {
      int s, t, x;
      cin >> s >> t >> x;
      fw.imos_add(s - 1, t, x);
    } else {
      int i;
      cin >> i;
      cout << fw.imos_get(i - 1) << "\n";
    }
  }
}