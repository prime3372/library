#define PROBLEM \
  "https://onlinejudge.u-aizu.ac.jp/courses/lesson/2/ITP1/1/ITP1_1_A"

#include "random/engine.hpp"
#include "util/io_float128.hpp"
#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using namespace cp;
using ll = long long;
using f128 = __float128;

f128 abs(f128 x) { return x < 0 ? -x : x; }

void test(f128 p10, int prec) {
  stringstream ss;
  ss << fixed << setprecision(prec);
  f128 x = uniform01();
  x *= x;
  x *= p10;
  if (uniform_bool()) x = -x;
  ss << x;
  f128 y;
  ss >> y;
  assert(abs(x - y) / x < 1e-32);
}
void tiny() { test(1e-30, 90); }
void small() { test(1, 60); }
void medium() { test(1e15, 45); }
void large() { test(1e30, 15); }
void huge() { test(1e60, 0); }

int main() {
  for (int i = 0; i < 10000; i++) tiny();
  for (int i = 0; i < 10000; i++) small();
  for (int i = 0; i < 10000; i++) medium();
  for (int i = 0; i < 10000; i++) large();
  for (int i = 0; i < 10000; i++) huge();
  cout << "Hello World\n";
}