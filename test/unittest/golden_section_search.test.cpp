#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "random/engine.hpp"
#include "util/golden_section_search.hpp"
#include <iostream>

using namespace std;
using namespace cp;
using ll = long long;

void test() {
  int c = uniform(1, int(1e9));
  auto f = [&](double x) -> double { return x + c / x; };
  auto ans = golden_section_search(f, 0.0, 1e9 + 10, 60);
  double sq = sqrt(c);
  assert(abs((ans.first - sq) / sq) < 1e-6);
  assert(abs((ans.second - f(sq)) / f(sq)) < 1e-6);
}

int main() {
  for (int i = 0; i < 500000; i++) test();
  cout << "Hello World\n";
}