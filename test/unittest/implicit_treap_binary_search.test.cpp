#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "ds/implicit_treap.hpp"
#include "random/engine.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

void test(int n, int q, ll bound) {
  vector<ll> a(n);
  for (int i = 0; i < n; i++) a[i] = uniform(-bound, bound);
  std::sort(a.begin(), a.end());
  implicit_treap<ll> t(a);
  while (q--) {
    int l = uniform(0, n - 1);
    int r = uniform(0, n - 1);
    if (l > r) swap(l, r);
    ll k = uniform(-2 * bound, 2 * bound);
    auto f = [&](ll x) { return x < k; };
    assert(t.binary_search(l, r, f) ==
           lower_bound(a.begin() + l, a.begin() + r, k) - a.begin());
  }
}
void small() { test(uniform(1, 100), 100, 10000); }
void large() { test(uniform(1, 100000), 100000, ll(1e18)); }
void narrow() { test(uniform(1, 100000), 100000, 10); }

int main() {
  for (int i = 0; i < 10000; i++) small();
  for (int i = 0; i < 10; i++) large();
  for (int i = 0; i < 10; i++) narrow();
  cout << "Hello World\n";
}