#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_5_B"

#include "ds/cumsum_2d.hpp"
#include <algorithm>
#include <iostream>

using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  cumsum_2d<int> cum(1001, 1001);
  for (int i = 0; i < n; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cum.imos_add(x1, y1, x2, y2, 1);
  }
  int ans = 0;
  for (int i = 0; i <= 1000; i++) {
    for (int j = 0; j <= 1000; j++) {
      ans = max(ans, cum.imos_get(i, j));
    }
  }
  cout << ans << "\n";
}