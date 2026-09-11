#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include "ds/wavelet_matrix.hpp"
#include "util/algo_utility.hpp"
#include "util/coordinate_compression.hpp"
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

int main() {
  constexpr int bit_width = 32;
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, q;
  cin >> n >> q;
  vector<unsigned int> x(n), y(n);
  vector<ll> w(n);
  for (int i = 0; i < n; i++) cin >> x[i] >> y[i] >> w[i];

  auto p = sort(x);
  wavelet_matrix<unsigned int> wm(n);
  for (int i = 0; i < n; i++) wm.set(i, y[p[i]]);
  wm.build();

  vector<vector<ll>> cum(bit_width, vector<ll>(n + 1));
  for (int i = 0; i < n; i++) {
    int k = i;
    for (int h = bit_width - 1; h >= 0; h--) {
      k = wm[h].next(k);
      cum[h][k + 1] = w[p[i]];
    }
  }
  for (int h = 0; h < bit_width; h++) {
    for (int i = 0; i < n; i++) {
      cum[h][i + 1] += cum[h][i];
    }
  }

  auto sum = [&](int l, int r, unsigned int u) -> ll {
    ll ans = 0;
    for (int h = bit_width - 1; h >= 0; h--) {
      int l0 = wm[h].next0(l);
      int r0 = wm[h].next0(r);
      if ((u >> h) & 1) {
        ans += cum[h][r0] - cum[h][l0];
        l = wm[h].next1(l);
        r = wm[h].next1(r);
      } else {
        l = l0;
        r = r0;
      }
    }
    return ans;
  };

  while (q--) {
    unsigned int l, d, r, u;
    cin >> l >> d >> r >> u;
    int l_lb = int(std::lower_bound(x.begin(), x.end(), l) - x.begin());
    int r_lb = int(std::lower_bound(x.begin(), x.end(), r) - x.begin());
    cout << sum(l_lb, r_lb, u) - sum(l_lb, r_lb, d) << "\n";
  }
}