#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/all/ITP2_7_C"

#include "ds/treap.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int q;
  cin >> q;
  treap<int, false> s;
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int x;
      cin >> x;
      s.insert(x);
      cout << s.size() << "\n";
    } else if (t == 1) {
      int x;
      cin >> x;
      cout << s.contains(x) << "\n";
    } else if (t == 2) {
      int x;
      cin >> x;
      s.erase(x);
    } else {
      int l, r;
      cin >> l >> r;
      int lb = s.lower_bound(l), ub = s.upper_bound(r);
      for (int i = lb; i < ub; i++) {
        cout << s[i] << "\n";
      }
    }
  }
}