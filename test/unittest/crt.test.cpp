#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "number/crt.hpp"
#include "number/enumerate_divisors.hpp"
#include "random/engine.hpp"
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

void test() {
  ll x = uniform(1LL, ll(1e18));
  auto divs = enumerate_divisors(x);
  int n = int(divs.size());
  shuffle(divs);
  int k = uniform(1, n);
  ll l = 1;
  vector<ll> r(k), m(k);
  for (int i = 0; i < k; i++) {
    m[i] = divs[i];
    r[i] = divs[0] % divs[i];
    l = lcm(l, divs[i]);
  }
  auto [ans_r, ans_m] = crt(r, m);
  assert(ans_r == divs[0] % l && ans_m == l);
}

void stress() {
  int max_m = 42;  // lcm(1, 2, ..., 42) < 2**63
  int t = 1000000;
  while (t--) {
    int n = uniform(1, 100);
    vector<ll> r(n), m(n);
    for (int i = 0; i < n; i++) {
      m[i] = uniform(1, max_m);
      r[i] = rng();
    }
    auto [ans_r, ans_m] = crt(r, m);
    assert((ans_m == 0 && ans_r == 0) || (0 <= ans_r && ans_r < ans_m));
  }
}

void empty() { assert((crt({}, {}) == std::pair{0LL, 1LL})); }

void solve() {
  int a, b;
  cin >> a >> b;
  cout << a + b << "\n";
}

int main() {
  for (int i = 0; i < 1000; i++) test();
  stress();
  empty();
  solve();
}