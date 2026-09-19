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

void random(int n, ll upper) {
  vector<ll> a(n);
  for (ll& x : a) x = uniform(0LL, upper);
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
void large() { random(uniform(1, 100000), ll(1e18)); }
void small() { random(uniform(1, 10), 100); }

void decreasing() {
  int n = uniform(1, 100000);
  vector<ll> a(n);
  for (ll& x : a) x = uniform(0LL, ll(1e18));
  sort(a.rbegin(), a.rend());
  a.erase(unique(a.begin(), a.end()), a.end());
  n = int(a.size());
  auto f = [&](ll i) -> ll { return a[i]; };
  auto ans = golden_section_search(f, 0, n - 1);
  assert(ans.first == n - 1);
  assert(ans.second == a[n - 1]);
}

void increasing() {
  int n = uniform(1, 100000);
  vector<ll> a(n);
  for (ll& x : a) x = uniform(0LL, ll(1e18));
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  n = int(a.size());
  auto f = [&](ll i) -> ll { return a[i]; };
  auto ans = golden_section_search(f, 0, n - 1);
  assert(ans.first == 0);
  assert(ans.second == a[0]);
}

int main() {
  for (int i = 0; i < 100; i++) large();
  for (int i = 0; i < 10000; i++) small();
  for (int i = 0; i < 10; i++) decreasing();
  for (int i = 0; i < 10; i++) increasing();
  cout << "Hello World\n";
}