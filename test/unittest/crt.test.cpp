#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "number/crt.hpp"
#include "number/enumerate_divisors.hpp"
#include "random/engine.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

void random_mod(int n) {
  constexpr int max_m = 42;  // lcm(1, 2, ..., 42) < 2**63
  vector<ll> r(n), m(n);
  for (int i = 0; i < n; i++) {
    m[i] = uniform(1, max_m);
    r[i] = rng();
  }
  auto [ans_r, ans_m] = crt(r, m);
  for (int i = 0; i < n; i++) {
    r[i] %= m[i];
    if (r[i] < 0) r[i] += m[i];
  }
  for (int i = 0; i < max_m; i++) {
    bool satisfy = true;
    for (int j = 0; j < n; j++) {
      if (i % m[j] != r[j]) {
        satisfy = false;
        break;
      }
    }
    assert((ans_m && i % ans_m == ans_r) == satisfy);
  }
}
void small() { random_mod(uniform(1, 100)); }
void large() { random_mod(uniform(1, 100000)); }

void has_answer() {
  ll x = uniform(1LL, ll(1e18));
  auto divs = enumerate_divisors(x);
  int n = int(divs.size());
  shuffle(divs);
  vector<ll> r(n), m(n);
  for (int i = 0; i < n; i++) {
    m[i] = divs[i];
    r[i] = divs[0] % divs[i];
  }
  auto [ans_r, ans_m] = crt(r, m);
  assert(ans_r == divs[0] % x && ans_m == x);
}

void empty() { assert(crt({}, {}) == make_pair(0LL, 1LL)); }

int main() {
  for (int i = 0; i < 100000; i++) small();
  for (int i = 0; i < 100; i++) large();
  for (int i = 0; i < 100; i++) has_answer();
  empty();
  cout << "Hello World\n";
}