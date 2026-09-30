#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "ds/offline_rectangle_add_rectangle_sum.hpp"
#include "random/engine.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

void check(int n, int q, int x, int y) {
  offline_rectangle_add_rectangle_sum<int, ll> data;
  vector<vector<ll>> grid(2 * x + 1, vector<ll>(2 * y + 1));
  for (int i = 0; i < n; i++) {
    int l = uniform(-x, x), r = uniform(-x, x);
    if (l > r) swap(l, r);
    int d = uniform(-y, y), u = uniform(-y, y);
    if (d > u) swap(d, u);
    int w = uniform(int(-1e9), int(1e9));
    data.add(l, d, r, u, w);
    for (int j = l; j < r; j++) {
      for (int k = d; k < u; k++) {
        grid[j + x][k + y] += w;
      }
    }
  }
  vector<ll> ans(q);
  for (int i = 0; i < q; i++) {
    int l = uniform(-x, x), r = uniform(-x, x);
    if (l > r) swap(l, r);
    int d = uniform(-y, y), u = uniform(-y, y);
    if (d > u) swap(d, u);
    data.sum(l, d, r, u);
    ll s = 0;
    for (int j = l; j < r; j++) {
      for (int k = d; k < u; k++) {
        s += grid[j + x][k + y];
      }
    }
    ans[i] = s;
  }
  assert(ans == data.run());
}
void small() {
  int n = uniform(0, 10);
  int q = uniform(0, 10);
  int x = uniform(0, 100);
  int y = uniform(0, 100);
  check(n, q, x, y);
}
void large() {
  int n = uniform(0, 100);
  int q = uniform(0, 100);
  int x = uniform(0, 1000);
  int y = uniform(0, 1000);
  check(n, q, x, y);
}

void stress() {
  int n = 100000;
  int q = 100000;
  int bound = 1000000;
  offline_rectangle_add_rectangle_sum<int, ll> data;
  for (int i = 0; i < n; i++) {
    int l = uniform(-bound, bound), r = uniform(-bound, bound);
    if (l > r) swap(l, r);
    int d = uniform(-bound, bound), u = uniform(-bound, bound);
    if (d > u) swap(d, u);
    data.add(l, d, r, u, 1);
  }
  for (int i = 0; i < q; i++) {
    int l = uniform(-bound, bound), r = uniform(-bound, bound);
    if (l > r) swap(l, r);
    int d = uniform(-bound, bound), u = uniform(-bound, bound);
    if (d > u) swap(d, u);
    data.sum(l, d, r, u);
  }
  for (ll x : data.run()) assert(ll(-4e17) <= x && x <= ll(4e17));
}

void solve() {
  int a, b;
  cin >> a >> b;
  cout << a + b << "\n";
}

int main() {
  for (int i = 0; i < 10000; i++) small();
  for (int i = 0; i < 100; i++) large();
  for (int i = 0; i < 5; i++) stress();
  solve();
}