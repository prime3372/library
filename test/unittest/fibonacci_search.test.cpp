#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "random/engine.hpp"
#include "other/fibonacci_search.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

void test(int n, ll bound) {
  vector<ll> a(n);
  for (ll& x : a) x = uniform(-bound, bound);
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  n = int(a.size());
  int arg = uniform(0, n - 1);
  std::reverse(a.end() - arg, a.end());
  std::rotate(a.begin(), a.end() - arg, a.end());
  auto f = [&](ll i) -> ll {
    assert(0 <= i && i < n);
    return a[i];
  };
  auto ans = fibonacci_search(f, 0, n - 1);
  assert(ans.first == arg);
  assert(ans.second == a[arg]);
}
void small() { test(uniform(1, 100), 10000); }
void large() { test(uniform(1, 100000), ll(1e18)); }

void solve() {
  int a, b;
  cin >> a >> b;
  cout << a + b << "\n";
}

int main() {
  for (int i = 0; i < 200000; i++) small();
  for (int i = 0; i < 200; i++) large();
  solve();
}