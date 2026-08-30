#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "ds/wavelet_matrix.hpp"
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  wavelet_matrix wm(n);
  for (int i = 0; i < n; i++) {
    int ai;
    cin >> ai;
    wm.set(i, ai);
  }
  wm.build();
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    cout << wm.kth_smallest(l, r, k) << "\n";
  }
}