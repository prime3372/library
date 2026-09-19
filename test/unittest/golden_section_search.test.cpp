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

int max_n = 10000;
ll max_a = 1000000000000000000LL;

void random() {
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
  assert(ans == make_pair(x, a[x]));
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
  assert(ans == make_pair(n - 1, a[n - 1]));
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
  assert(ans == make_pair(0, a[0]));
}

int main() {
  for (int i = 0; i < 100; i++) random();
  for (int i = 0; i < 10; i++) decreasing();
  for (int i = 0; i < 10; i++) increasing();
  cout << "Hello World\n";
}