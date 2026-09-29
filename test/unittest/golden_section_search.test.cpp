#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "random/engine.hpp"
#include "util/golden_section_search.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace cp;
using ll = long long;
using ld = long double;

void test1() {
  int c = uniform(1, int(1e9));
  auto f = [&](ld x) -> ld { return x + c / x; };
  auto ans = golden_section_search(f, 0, 1e9 + 1, 100);
  double sq = sqrt(c);
  assert(abs((ans.first - sq) / sq) < 1e-6);
  assert(abs((ans.second - f(sq)) / f(sq)) < 1e-6);
}

void test2() {
  int c = uniform(int(-1e9), int(1e9));
  auto f = [&](ld x) -> ld { return abs(x - c); };
  auto ans = golden_section_search(f, -1e9 - 1, 1e9 + 1, 100);
  assert(abs(ans.first - c) / c < 1e-6);
  assert(abs(ans.second) < 1e-6);
}

void test3() {
  auto f = [&](ld x) -> ld { return x; };
  auto ans = golden_section_search(f, 0, 1, 44);
  assert(abs(ans.first) < 1e-9);
  assert(abs(ans.second) < 1e-9);
}

int main() {
  for (int i = 0; i < 500000; i++) test1();
  for (int i = 0; i < 500000; i++) test2();
  test3();
  cout << "Hello World\n";
}