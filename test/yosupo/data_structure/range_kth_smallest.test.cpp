#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "ds/range_kth_smallest.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  std::vector<int> a(n);
  for (int& ai : a) cin >> ai;
  range_kth_smallest kth(a);
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    cout << kth.query(l, r, k) << "\n";
  }
}