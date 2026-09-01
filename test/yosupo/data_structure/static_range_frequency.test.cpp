#define PROBLEM "https://judge.yosupo.jp/problem/static_range_frequency"

#include "ds/hash_map.hpp"
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  hash_map<int, vector<int>> idx;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    idx[a].push_back(i);
  }
  while (q--) {
    int l, r, x;
    cin >> l >> r >> x;
    auto& v = idx[x];
    auto a = lower_bound(v.begin(), v.end(), l);
    auto b = lower_bound(v.begin(), v.end(), r);
    cout << b - a << "\n";
  }
}