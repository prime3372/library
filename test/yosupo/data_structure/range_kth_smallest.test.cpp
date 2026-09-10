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
  wavelet_matrix<unsigned int> wm(n);
  for (int i = 0; i < n; i++) {
    int ai;
    cin >> ai;
    wm.set(i, ai);
  }
  wm.build();
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    unsigned int ans = 0;
    for (int h = 31; h >= 0; h--) {
      int l0 = wm[h].child0(l), r0 = wm[h].child0(r);
      if (r0 - l0 > k) {
        l = l0;
        r = r0;
      } else {
        ans |= 1 << h;
        k -= r0 - l0;
        l = wm[h].child1(l);
        r = wm[h].child1(r);
      }
    }
    cout << ans << "\n";
  }
}