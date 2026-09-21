#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "random/engine.hpp"
#include "util/golden_section_search.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;

void test(int n, ll limit) {
  vector<ll> a(n);
  for (ll& x : a) x = uniform(-limit, limit);
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  n = int(a.size());
  int arg = uniform(0, n - 1);
  std::reverse(a.end() - arg, a.end());
  std::rotate(a.begin(), a.end() - arg, a.end());
  auto f = [&](ll i) -> ll { return a[i]; };
  auto ans = golden_section_search(f, 0, n - 1);
  assert(ans.first == arg);
  assert(ans.second == a[arg]);
}
void small() { test(uniform(1, 100), 10000); }
void large() { test(uniform(1, 100000), ll(1e18)); }
void narrow() { test(uniform(1, 100000), 10); }

int main() {
  for (int i = 0; i < 100000; i++) small();
  for (int i = 0; i < 100; i++) large();
  for (int i = 0; i < 100; i++) narrow();
  cout << "Hello World\n";
}