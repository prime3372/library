#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_frequency"

#include "ds/hash-map.hpp"
#include "ds/Treap.hpp"
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
  HashMap<int, Treap<int, false>> idx;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    idx[a[i]].insert(i);
  }
  while (q--) {
    int t;
    cin >> t;
    if (t == 0) {
      int k, v;
      cin >> k >> v;
      idx[a[k]].erase(k);
      idx[v].insert(k);
      a[k] = v;
    } else {
      int l, r, x;
      cin >> l >> r >> x;
      cout << idx[x].lower_bound(r) - idx[x].lower_bound(l) << "\n";
    }
  }
}