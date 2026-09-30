#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "ds/offline_rectangle_add_rectangle_sum.hpp"
#include "random/engine.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

void test(int n, int q, int x, int y) {
  offline_rectangle_add_rectangle_sum<int, ll> data;
  vector<vector<ll>> grid(x, vector<ll>(y));
  for (int i = 0; i < n; i++) {
    int l = uniform(0, x), r = uniform(0, x);
    if (l > r) swap(l, r);
    int d = uniform(0, y), u = uniform(0, y);
    if (d > u) swap(d, u);
    int w = uniform(int(-1e9), int(1e9));
    data.add(l, d, r, u, w);
    for (int j = l; j < r; j++) {
      for (int k = d; k < u; k++) {
        grid[j][k] += w;
      }
    }
  }
  vector<ll> ans(q);
  for (int i = 0; i < q; i++) {
    int l = uniform(0, x), r = uniform(0, x);
    if (l > r) swap(l, r);
    int d = uniform(0, y), u = uniform(0, y);
    if (d > u) swap(d, u);
    data.sum(l, d, r, u);
    ll s = 0;
    for (int j = l; j < r; j++) {
      for (int k = d; k < u; k++) {
        s += grid[j][k];
      }
    }
    ans[i] = s;
  }
  assert(ans == data.run());
}
void small() {
  int n = uniform(0, 50);
  int q = uniform(0, 50);
  int x = uniform(0, 100);
  int y = uniform(0, 100);
  test(n, q, x, y);
}
void large() {
  int n = uniform(0, 500);
  int q = uniform(0, 500);
  int x = uniform(0, 1000);
  int y = uniform(0, 1000);
  test(n, q, x, y);
}

void solve() {
  int a, b;
  cin >> a >> b;
  cout << a + b << "\n";
}

int main() {
  for (int i = 0; i < 10000; i++) small();
  for (int i = 0; i < 100; i++) large();
  solve();
}