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

void test(int n) {
  constexpr int max_m = 42; // lcm(1, 2, ..., 42) < 2**63
  vector<ll> r(n), m(n);
  for (int i = 0; i < n; i++) {
    m[i] = uniform(1, max_m);
    r[i] = uniform(0LL, m[i] - 1);
  }
  auto [ans_r, ans_m] = crt(r, m);
  for (int i = 0; i < max_m; i++) {
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
void small() { test(uniform(1, 10)); }
void large() { test(uniform(1, 100000)); }

void empty() { assert(crt({}, {}) == make_pair(0LL, 1LL)); }

int main() {
  for (int i = 0; i < 100000; i++) small();
  for (int i = 0; i < 10; i++) large();
  empty();
  cout << "Hello World\n";
}