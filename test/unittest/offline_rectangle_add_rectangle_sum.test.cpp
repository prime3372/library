#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "ds/offline_rectangle_add_rectangle_sum.hpp"
#include "random/engine.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

void test(int n, int q, int x, int y) {
  offline_rectangle_add_rectangle_sum<int, ll> sum;
  vector<vector<ll>> grid(x, vector<ll>(y));
  for (int i = 0; i < n; i++) {
    int l = uniform(0, x), r = uniform(0, x);
    if (l > r) swap(l, r);
    int d = uniform(0, y), u = uniform(0, y);
    if (d > u) swap(d, u);
    int w = uniform(int(-1e9), int(1e9));
    sum.add(l, d, r, u, w);
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
    sum.sum(l, d, r, u);
    ll s = 0;
    for (int j = l; j < r; j++) {
      for (int k = d; k < u; k++) {
        s += grid[j][k];
      }
    }
    ans[i] = s;
  }
  assert(ans == sum.run());
}
void small() {
  int n = uniform(0, 10), q = uniform(0, 10);
  int x = uniform(0, 100), y = uniform(0, 100);
  test(n, q, x, y);
}
void large() {
  int n = uniform(0, 100), q = uniform(0, 100);
  int x = uniform(0, 1000), y = uniform(0, 1000);
  test(n, q, x, y);
}

int main() {
  for (int i = 0; i < 10000; i++) small();
  for (int i = 0; i < 100; i++) large();
  cout << "Hello World\n";
}