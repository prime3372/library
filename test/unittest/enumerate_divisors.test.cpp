#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "number/count_divisors.hpp"
#include "number/enumerate_divisors.hpp"
#include "random/engine.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

void check(int n) {
  auto divs = enumerate_divisors(n);
  for (int i = 1; i < n; i++) {
    bool is_divisor = n % i == 0;
    auto lb = lower_bound(divs.begin(), divs.end(), i);
    auto ub = upper_bound(divs.begin(), divs.end(), i);
    assert(ub - lb <= 1);
    assert(is_divisor == (lb != ub));
  }
}

void stress(ll n) {
  auto divs = enumerate_divisors(n);
  assert(int(divs.size()) == count_divisors(n));
}

void solve() {
  int a, b;
  cin >> a >> b;
  cout << a + b << "\n";
}

int main() {
  for (int i = 1; i <= 1000; i++) check(i);
  for (int i = 0; i < 100; i++) check(uniform(1001, 1000000));
  for (int i = 0; i < 100; i++) stress(uniform(1LL, ll(1e18)));
  solve();
}