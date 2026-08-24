#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/all/DPL_3_B"

#include "ds/cartesian_tree.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

ll largest_rectanle_in_a_histogram(int n, const vector<ll>& a) {
  cartesian_tree<false> cart(a);
  vector<int> sub(n);
  auto dfs = [&](auto self, int v) -> int {
    if (v == -1) return 0;
    sub[v] = 1;
    sub[v] += self(self, cart.left[v]);
    sub[v] += self(self, cart.right[v]);
    return sub[v];
  };
  dfs(dfs, cart.root);
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans = max(ans, a[i] * sub[i]);
  }
  return ans;
}

int main() {
  int h, w;
  cin >> h >> w;
  vector<vector<bool>> c(h, vector<bool>(w));
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      bool cij;
      cin >> cij;
      c[i][j] = cij;
    }
  }
  vector<vector<ll>> cnt(h, vector<ll>(w));
  for (int j = 0; j < w; j++) {
    cnt[0][j] = !c[0][j];
    for (int i = 1; i < h; i++) {
      if (c[i][j]) cnt[i][j] = 0;
      else cnt[i][j] = cnt[i - 1][j] + 1;
    }
  }
  ll ans = 0;
  for (int i = 0; i < h; i++) {
    ans = max(ans, largest_rectanle_in_a_histogram(w, cnt[i]));
  }
  cout << ans << "\n";
}