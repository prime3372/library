#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_frequency"

#include "ds/hash_map.hpp"
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
  hash_map<int, treap<int, false>> idx;
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