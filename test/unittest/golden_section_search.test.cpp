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

int max_n = 50000;
ll max_a = 1000000000000000000LL;

void large() {
  int n = uniform(1, max_n);
  vector<ll> a(n);
  for (ll& x : a) x = uniform(0LL, max_a);
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  n = int(a.size());
  int x = uniform(0, n - 1);
  std::reverse(a.end() - x, a.end());
  std::rotate(a.begin(), a.end() - x, a.end());
  for (int i = 0; i < x; i++) assert(a[i] > a[i + 1]);
  for (int i = x; i < n - 1; i++) assert(a[i] < a[i + 1]);
  auto f = [&](ll i) -> ll { return a[i]; };
  auto ans = golden_section_search(f, 0, n - 1);
  assert(ans.first == x);
  assert(ans.second == a[x]);
}

void small() {
  int n = uniform(1, 10);
  vector<int> a(n);
  for (int& x : a) x = uniform(0, 100);
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  n = int(a.size());
  int x = uniform(0, n - 1);
  std::reverse(a.end() - x, a.end());
  std::rotate(a.begin(), a.end() - x, a.end());
  for (int i = 0; i < x; i++) assert(a[i] > a[i + 1]);
  for (int i = x; i < n - 1; i++) assert(a[i] < a[i + 1]);
  auto f = [&](ll i) -> int { return a[i]; };
  auto ans = golden_section_search(f, 0, n - 1);
  assert(ans.first == x);
  assert(ans.second == a[x]);
}

void decreasing() {
  int n = uniform(1, max_n);
  vector<ll> a(n);
  for (ll& x : a) x = uniform(0LL, max_a);
  sort(a.rbegin(), a.rend());
  a.erase(unique(a.begin(), a.end()), a.end());
  n = int(a.size());
  for (int i = 0; i < n - 1; i++) assert(a[i] > a[i + 1]);
  auto f = [&](ll i) -> ll { return a[i]; };
  auto ans = golden_section_search(f, 0, n - 1);
  assert(ans.first == n - 1);
  assert(ans.second == a[n - 1]);
}

void increasing() {
  int n = uniform(1, max_n);
  vector<ll> a(n);
  for (ll& x : a) x = uniform(0LL, max_a);
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  n = int(a.size());
  for (int i = 0; i < n - 1; i++) assert(a[i] < a[i + 1]);
  auto f = [&](ll i) -> ll { return a[i]; };
  auto ans = golden_section_search(f, 0, n - 1);
  assert(ans.first == 0);
  assert(ans.second == a[0]);
}

int main() {
  for (int i = 0; i < 100; i++) large();
  for (int i = 0; i < 100; i++) small();
  for (int i = 0; i < 10; i++) decreasing();
  for (int i = 0; i < 10; i++) increasing();
  cout << "Hello World\n";
}