#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "random/engine.hpp"
#include "number/crt.hpp"
#include "number/enumerate_divisors.hpp"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

void small() {
  int x = uniform(1, 1000);
  auto divs = enumerate_divisors(x);
  int n = uniform(1, int(divs.size()));
  shuffle(divs.begin(), divs.end(), rng);
  vector<ll> r(n), m(n);
  for (int i = 0; i < n; i++) {
    m[i] = divs[i];
    r[i] = uniform(0LL, m[i] - 1);
  }
  auto [ans_r, ans_m] = crt(r, m);
  for (int i = 0; i < x; i++) {
    bool satisfy = true;
    for (int j = 0; j < n; j++) {
      if (i % m[j] != r[j] % m[j]) {
        satisfy = false;
        break;
      }
    }
    assert((ans_m && i % ans_m == ans_r) == satisfy);
  }
}

void has_ans() {
  ll x = uniform(1LL, ll(1e18));
  auto divs = enumerate_divisors(x);
  int n = int(divs.size());
  shuffle(divs.begin(), divs.end(), rng);
  ll d = divs[uniform(0, n - 1)];
  if (d == x) d = 0;
  vector<ll> r(n), m(n);
  for (int i = 0; i < n; i++) {
    m[i] = divs[i];
    r[i] = d % m[i];
  }
  auto [ans_r, ans_m] = crt(r, m);
  assert(ans_r == d && ans_m == x);
}

void empty() { assert(crt({}, {}) == make_pair(0LL, 1LL)); }

int main() {
  for (int i = 0; i < 100; i++) small();
  for (int i = 0; i < 100; i++) has_ans();
  empty();
  cout << "Hello World\n";
}