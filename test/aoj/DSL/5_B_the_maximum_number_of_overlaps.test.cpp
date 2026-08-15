#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/all/DSL_5_B"

#include "algebra/min.hpp"
#include "ds/cumsum_2d.hpp"

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < int(b); i++)
using namespace std;
using namespace cp;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  cumsum_2d<int> cum(1001, 1001);
  rep(i, 0, n) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cum.imos_add(x1, y1, x2, y2, 1);
  }
  int ans = 0;
  rep(i, 0, 1001) {
    rep(j, 0, 1001) {
      ans = max(ans, cum.imos_get(i, j));
    }
  }
  cout << ans << "\n";
}