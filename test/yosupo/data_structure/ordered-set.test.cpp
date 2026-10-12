#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "ds/treap.hpp"

#include <iostream>
#include <vector>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int& x : a) cin >> x;
  treap<int, false> s(a);
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int x;
      cin >> x;
      s.insert(x);
    } else if (t == 1) {
      int x;
      cin >> x;
      s.erase(x);
    } else if (t == 2) {
      int x;
      cin >> x;
      x--;
      cout << (x < s.size() ? s[x] : -1) << "\n";
    } else if (t == 3) {
      int x;
      cin >> x;
      cout << s.upper_bound(x) << "\n";
    } else if (t == 4) {
      int x;
      cin >> x;
      int ub = s.upper_bound(x);
      cout << (ub == 0 ? -1 : s[ub - 1]) << "\n";
    } else {
      int x;
      cin >> x;
      int lb = s.lower_bound(x);
      cout << (lb == s.size() ? -1 : s[lb]) << "\n";
    }
  }
}