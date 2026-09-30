#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "random/engine.hpp"
#include "other/golden_section_search.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace cp;
using ll = long long;
using ld = long double;

void test1() {
  int c = uniform(int(-1e4), int(1e4));
  auto f = [&](ld x) -> ld { return abs(x - c); };
  auto ans = golden_section_search(f, -5e4, 5e4, 44);
  assert(abs(ans.first - c) < 1e-4);
  assert(0 <= ans.second && ans.second < 1e-4);
}

void test2() {
  int c = uniform(int(-1e8), int(1e8));
  auto f = [&](ld x) -> ld { return abs(x - c); };
  auto ans = golden_section_search(f, -5e8, 5e8, 87);
  assert(abs(ans.first - c) < 1e-9);
  assert(0 <= ans.second && ans.second < 1e-9);
}

void solve() {
  int a, b;
  cin >> a >> b;
  cout << a + b << "\n";
}

int main() {
  for (int i = 0; i < 1000; i++) test1();
  for (int i = 0; i < 1000000; i++) test2();
  solve();
}